#include <string.h>

#include "reflection.h"
#include "reflection_int.h"


func_t refl_find(const char *name)
{
    for (int i = 0; i < __symtab_entries; i++)
        if (!strcmp(__strtab + __symtab[i].st_name, name))
            return __symtab[i].st_value + __relocation;

    return 0;
}
