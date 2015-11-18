#include <elf.h>
#include <stdbool.h>
#include <stdio.h>

#include "reflection.h"
#include "reflection_int.h"


bool refl_each_next(func_t *fptr)
{
    int i = *fptr ? refl_hash_find(*fptr)->symtab_idx + 1 : 0;

    for (; i < __symtab_entries; i++)
    {
        uintptr_t value = __symtab[i].st_value + __relocation;
        if ((ELF64_ST_TYPE(__symtab[i].st_info) == STT_FUNC) && refl_is_virtual(value))
        {
            *fptr = value;
            return true;
        }
    }

    return false;
}
