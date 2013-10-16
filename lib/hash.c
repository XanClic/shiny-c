#include <stdint.h>
#include <stdlib.h>

#include "reflection.h"
#include "reflection_int.h"


#define VF_HT_BITS 8

static struct vf_ht_entry *vf_ht[1 << VF_HT_BITS];


static unsigned hash_vf(func_t func)
{
    return (func >> 4) & ((1 << VF_HT_BITS) - 1);
}


const struct vf_ht_entry *refl_hash_find(func_t func)
{
    unsigned hash = hash_vf(func);

    for (struct vf_ht_entry *e = vf_ht[hash]; e != NULL; e = e->next)
        if (e->vf == func)
            return e;

    return NULL;
}


struct vf_ht_entry *refl_hash_insert(func_t func)
{
    unsigned hash = hash_vf(func);
    struct vf_ht_entry **ep;

    for (ep = &vf_ht[hash]; *ep != NULL; ep = &(*ep)->next)
        if ((*ep)->vf == func)
            return *ep;

    *ep = calloc(1, sizeof(**ep));
    (*ep)->vf = func;
    return *ep;
}
