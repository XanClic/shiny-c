#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "elf64.h"
#include "reflection.h"
#include "reflection_int.h"


void *__image;
Elf64_Sym *__symtab;
int __symtab_entries;
const char *__strtab;
uintptr_t __vmin, __vmax;
struct virt_trampoline *__trampolines;

static const uint64_t trampoline_code[] = {
    0x57560000003a058f,
    0x4800000041358d48,
    0xa548000000323d8b,
    0x002615ff5e5fa548,
    0x35358d4857560000,
    0x00163d8b48000000,
    0x5e5fa548a5480000,
    0x90900000000225ff
};


static void collect(void) __attribute__((constructor));

static void collect(void)
{
    FILE *fp = fopen("/proc/self/exe", "rb");

    if (!fp)
    {
        fprintf(stderr, "Could not open myself\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    rewind(fp);

    void *buf = malloc(sz);
    fread(buf, sz, 1, fp);
    rewind(fp);

    Elf64_Ehdr *ehdr = buf;
    Elf64_Shdr *shdr = (Elf64_Shdr *)((uintptr_t)buf + ehdr->e_shoff);
    const char *shstrtab = (const char *)((uintptr_t)buf + shdr[ehdr->e_shstrndx].sh_offset);

    const struct refl_annotation **annotation_start = NULL, **annotation_end = NULL;

    uintptr_t tmin = 0, tmax = 0;

    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        if (!strcmp(shstrtab + shdr[i].sh_name, ".symtab"))
        {
            assert(shdr[i].sh_entsize == sizeof(Elf64_Sym));
            __symtab = (Elf64_Sym *)((uintptr_t)buf + shdr[i].sh_offset);
            __symtab_entries = shdr[i].sh_size / shdr[i].sh_entsize;
        }
        else if (!strcmp(shstrtab + shdr[i].sh_name, ".strtab"))
            __strtab = (const char *)((uintptr_t)buf + shdr[i].sh_offset);
        else if (!strcmp(shstrtab + shdr[i].sh_name, ".text"))
        {
            tmin = shdr[i].sh_addr;
            tmax = shdr[i].sh_addr + shdr[i].sh_size;
        }
        else if (!strcmp(shstrtab + shdr[i].sh_name, "refl_annotations"))
        {
            annotation_start = (const struct refl_annotation **)(shdr[i].sh_addr);
            annotation_end   = (const struct refl_annotation **)(shdr[i].sh_addr + shdr[i].sh_size);
        }
    }

    assert(__symtab);
    assert(__strtab);
    assert(tmin && tmax);

    int virt_func_count = 0;

    __vmin = tmax;
    __vmax = tmin;

    for (int i = 0; i < __symtab_entries; i++)
    {
        if ((ST_TYPE(__symtab[i].st_info) == STT_FUNCTION) && (__symtab[i].st_value >= tmin) && (__symtab[i].st_value < tmax) && !(__symtab[i].st_value & 0xf))
        {
            virt_func_count++;

            if (__symtab[i].st_value < __vmin)
                __vmin = __symtab[i].st_value;
            if (__symtab[i].st_value > __vmax)
                __vmax = __symtab[i].st_value;
        }
    }

    uintptr_t pg_start = __vmin & ~0xffful;
    uintptr_t pg_size  = (__vmax - pg_start + 0xfff) & ~0xffful;

    mprotect((void *)pg_start, pg_size, PROT_READ | PROT_WRITE | PROT_EXEC);

    __trampolines = mmap(NULL, virt_func_count * sizeof(struct virt_trampoline), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    for (int i = 0, vfi = 0; i < __symtab_entries; i++)
    {
        if ((ST_TYPE(__symtab[i].st_info) == STT_FUNCTION) && refl_is_virtual(__symtab[i].st_value))
        {
            struct vf_ht_entry *e = refl_hash_insert(__symtab[i].st_value);

            e->symtab_idx = i;
            memcpy(e->prologue, (void *)__symtab[i].st_value, 16);
            e->trampoline = &__trampolines[vfi++];

            *e->trampoline = (struct virt_trampoline){
                .code = {
                    trampoline_code[0],
                    trampoline_code[1],
                    trampoline_code[2],
                    trampoline_code[3],
                    trampoline_code[4],
                    trampoline_code[5],
                    trampoline_code[6],
                    trampoline_code[7]
                },
                .target = __symtab[i].st_value,
                .prologue = {
                    e->prologue[0],
                    e->prologue[1]
                },
            };
        }
    }

    for (const struct refl_annotation **ap = annotation_start; ap < annotation_end; ap++)
    {
        struct annotation_entry *ae = malloc(sizeof(*ae));
        ae->annotation = **ap;

        assert(refl_hash_find(ae->annotation.func));
        struct vf_ht_entry *e = refl_hash_insert(ae->annotation.func);

        ae->next = e->annotation_list;
        e->annotation_list = ae;
    }

    refl_foreach(func)
    {
        // FIXME: This takes quadratic time, though it shouldn't.
        int siglen = 0;
        for (int i = REFL_ANNOTATION_FUNCSIG_PAR_TYPE; i <= REFL_ANNOTATION_FUNCSIG_RET_TYPE; i++)
        {
            const char *sig = refl_get_annotation(func, i);
            siglen += sig ? strlen(sig) : 0;
        }

        if (siglen)
        {
            struct vf_ht_entry *e = refl_hash_insert(func);

            char *signature = calloc(siglen + 1, 1);
            e->signature = signature;

            const char *ret = refl_get_annotation(func, REFL_ANNOTATION_FUNCSIG_RET_TYPE);
            assert(ret);

            strcat(signature, ret);

            for (int i = REFL_ANNOTATION_FUNCSIG_PAR_TYPE; i < REFL_ANNOTATION_FUNCSIG_RET_TYPE; i++)
            {
                const char *par = refl_get_annotation(func, i);
                if (!par)
                    break;
                strcat(signature, par);
            }

            assert(strlen(signature) == siglen);
        }
    }
}
