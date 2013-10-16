#include <stdio.h>

#include "reflection.h"
#include "reflection-funcsig.h"

refl_generate(void, foo, int, int);
void foo(int x, int y)
{
    printf("foo %i %i\n", x, y);
}

refl_generate(void, bar, int, int);
void bar(int x, int y)
{
    printf("bar %x %x\n", x, y);
}

refl_generate(void, print_target, const char *);
void print_target(const char *func)
{
    printf("%s() points to %s()\n", func, refl_get_name(refl_get_target(refl_find(func))));
}

refl_generate(void, puts_wrapper, const char *);
refl_annotate(puts_wrapper, 0, "print");
void puts_wrapper(const char *s)
{
    puts(s);
}

refl_generate(double, print_stuff, float, long long);
double print_stuff(float x, long long y)
{
    printf("%g %#llx\n", x, y);
    return 6.6 / x;
}
