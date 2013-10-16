#include <stdbool.h>
#include <stdio.h>

#include "reflection.h"
#include "reflection_int.h"


bool refl_each_next(func_t *fptr)
{
    int i = *fptr ? refl_hash_find(*fptr)->symtab_idx + 1 : 0;

    for (; i < __symtab_entries; i++)
    {
        if ((ST_TYPE(__symtab[i].st_info) == STT_FUNCTION) && refl_is_virtual(__symtab[i].st_value))
        {
            *fptr = __symtab[i].st_value;
            return true;
        }
    }

    return false;
}
