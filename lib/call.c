#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reflection.h"
#include "reflection_int.h"


extern uintptr_t __asm_call(func_t func, uintptr_t *iargv, int iargc, double *fpargv, int fpargc);


// fetch integer
#define fi(c, type) case c: ib[ibi++] = (uintptr_t)va_arg(args, type); break;
// store integer result
#define sir(c, type) case c: *(type *)result_ptr = (type)ib[0]; break;
// store floating point result
#define sfr(c, type) case c: *(type *)result_ptr = (type)fb[0]; break;


static void raw_call(const struct vf_ht_entry *e, const char *sig, va_list args)
{
    void *result_ptr = (sig[0] == 'v') ? NULL : va_arg(args, void *);
    while (!islower(*(sig++)));

    // integer block
    uintptr_t *ib = malloc(6 * sizeof(*ib));
    // integer block index
    int ibi = 0;

    // floating point block
    double *fb = malloc(8 * sizeof(*fb));
    // floating point block index
    int fbi = 0;

    while (*sig)
    {
        assert(ibi < 6);

        switch (*sig)
        {
            case 'v':
                sig++;
                continue;
            fi('c', int)
            fi('a', int)
            fi('h', int)
            fi('s', int)
            fi('t', int)
            fi('i', int)
            fi('j', unsigned)
            fi('l', long)
            fi('m', unsigned long)
            fi('x', long long)
            fi('y', unsigned long long)
            fi('P', void *)
            case 'f':
                *(float *)&fb[fbi++] = (float)va_arg(args, double);
                break;
            case 'd':
                fb[fbi++] = va_arg(args, double);
                break;
            default:
                assert(0);
        }

        while (!islower(*(sig++)));
    }

    __asm_call(e->vf, ib, ibi, fb, fbi);

    switch (e->signature[0])
    {
        case 'v': break;
        sir('c', char)
        sir('a', signed char)
        sir('h', unsigned char)
        sir('s', short)
        sir('t', unsigned short)
        sir('i', int)
        sir('j', unsigned)
        sir('l', long)
        sir('m', unsigned long)
        sir('x', long long)
        sir('y', unsigned long long)
        sir('P', void *)
        sfr('f', float)
        sfr('d', double)
        default:
            assert(0);
    }

    free(ib);
    free(fb);
}


void refl_call(func_t func, ...)
{
    va_list args;
    va_start(args, func);

    const struct vf_ht_entry *e = refl_hash_find(func);
    assert(e);

    const char *sig = e->signature;
    assert(sig);

    raw_call(e, sig, args);

    va_end(args);
}


void refl_call_verify(func_t func, const char *expsig, ...)
{
    va_list args;
    va_start(args, expsig);

    const struct vf_ht_entry *e = refl_hash_find(func);
    assert(e);

    const char *sig = e->signature;
    assert(sig);
    if (strcmp(sig, expsig))
    {
        fprintf(stderr, "Cannot dynamically call function: Expected signature (%s) differs from actual one (%s)\n", expsig, sig);
        assert(0);
    }

    raw_call(e, sig, args);

    va_end(args);
}
