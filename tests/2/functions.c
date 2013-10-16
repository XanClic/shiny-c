#include <stdio.h>

#include "reflection.h"

void foo(int x, int y)
{
    printf("foo %i %i\n", x, y);
}

void bar(int x, int y)
{
    printf("bar %x %x\n", x, y);
}

void print_target(const char *func)
{
    printf("%s() points to %s()\n", func, refl_get_name(refl_get_target(refl_find(func))));
}

void puts_wrapper(const char *s)
{
    puts(s);
}
refl_annotate(puts_wrapper, 0, "print");

double print_stuff(float x, long long y)
{
    printf("%g %#llx\n", x, y);
    return 6.6 / x;
}
