#include <stdbool.h>
#include <stddef.h>

#include "reflection.h"
#include "reflection_int.h"


const char *refl_get_annotation(func_t func, enum refl_annotation_type type)
{
    const struct vf_ht_entry *e = refl_hash_find(func);
    if (!e)
        return NULL;

    for (struct annotation_entry *ae = e->annotation_list; ae != NULL; ae = ae->next)
        if (ae->annotation.type == type)
            return ae->annotation.data;

    return NULL;
}


bool refl_each_annotation_next(func_t func, const struct refl_annotation **anno)
{
    const struct vf_ht_entry *e = refl_hash_find(func);
    if (!e)
        return false;

    if (!*anno)
        *anno = &e->annotation_list->annotation;
    else
        *anno = &((const struct annotation_entry *)*anno)->next->annotation;

    return *anno != NULL;
}
