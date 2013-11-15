#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "reflection.h"

extern void print_target(const char *);
extern void foo(int, int);
extern void bar();

int main(void)
{
    print_target("foo");
    foo(42, 66);

    refl_assign((func_t)foo, (func_t)bar);

    print_target("foo");
    foo(42, 66);


    printf("Accessible functions and their annotations:\n");
    refl_foreach(vfunc)
    {
        printf(" - %s()\n", refl_get_name(vfunc));
        refl_foreach_annotation(vfunc, anno)
            printf("    - %x: %s\n", anno->type, anno->data);
    }


    refl_foreach(vfunc)
        if (!strcmp(refl_get_annotation(vfunc, 0) ?: "", "print"))
            refl_call_verify(vfunc, "vPKc", "Dynamic call successful");

    double result;
    refl_call(refl_find("print_stuff"), &result, 4.2f, LLONG_MAX);
    printf("=> call result: %g\n", result);


    refl_foreach(vfunc)
        if (!strcmp(refl_get_annotation(vfunc, 0) ?: "", "print"))
            refl_dcall(vfunc, void, "And this is just doing it the simple (and boring) way.");


    return 0;
}
