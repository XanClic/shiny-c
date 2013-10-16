#include <stdbool.h>

#include "reflection.h"
#include "reflection_int.h"


bool refl_is_virtual(func_t func)
{
    return (func >= __vmin) && (func < __vmax);
}
