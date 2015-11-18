#ifndef REFLECTION_INT_H
#define REFLECTION_INT_H

#include <elf.h>
#include <stdint.h>

#include "reflection.h"


struct virt_trampoline
{
    uint64_t code[8];
    uint64_t scratch_ret;
    uint64_t target;
    uint64_t prologue[2];
    uint64_t trampoline[2];
};

struct annotation_entry
{
    struct refl_annotation annotation;
    struct annotation_entry *next;
};

struct vf_ht_entry
{
    struct vf_ht_entry *next;
    func_t vf;
    int symtab_idx;
    uint64_t prologue[2];
    struct virt_trampoline *trampoline;
    struct annotation_entry *annotation_list;
    const char *signature;
};


extern uintptr_t __vmin, __vmax, __relocation;
extern const char *__strtab;
extern Elf64_Sym *__symtab;
extern int __symtab_entries;


const struct vf_ht_entry *refl_hash_find(func_t func);
struct vf_ht_entry *refl_hash_insert(func_t func);

#endif
