#include <stddef.h>

#include "reflection.h"
#include "reflection_int.h"


const char *refl_get_name(func_t func)
{
    const struct vf_ht_entry *e = refl_hash_find(func);
    return e ? __strtab + __symtab[e->symtab_idx].st_name : NULL;
}


func_t refl_get_target(func_t func)
{
    const struct vf_ht_entry *e = refl_hash_find(func);
    return e ? e->trampoline->target : 0;
}
