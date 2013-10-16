#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "reflection.h"
#include "reflection_int.h"


static void establish_trampoline(const struct vf_ht_entry *e)
{
    *(uint16_t *)(e->vf + 0) = 0x25ff;
    *(uint32_t *)(e->vf + 2) = 0;
    *(uint64_t *)(e->vf + 6) = (uintptr_t)e->trampoline;

    memcpy(e->trampoline->trampoline, (void *)e->vf, 16);
}


void refl_assign(func_t dest, func_t src)
{
    const struct vf_ht_entry *de = refl_hash_find(dest);

    if (src == dest)
        memcpy((void *)dest, de->prologue, 16);
    else if (refl_is_virtual(src))
    {
        const struct vf_ht_entry *se = refl_hash_find(src);

        if (de->signature && se->signature && strcmp(de->signature, se->signature))
        {
            fprintf(stderr, "Cannot redirect function %#lx (%s %s) to %#lx (%s %s); signatures differ\n", dest, de->signature, refl_get_name(dest), src, se->signature, refl_get_name(src));
            assert(0);
        }

        memcpy(de->trampoline->prologue, se->prologue, 16);
        establish_trampoline(de);
    }
    else
    {
        memcpy(de->trampoline->prologue, (void *)src, 16);
        establish_trampoline(de);
    }

    de->trampoline->target = src;
}
