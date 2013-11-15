#ifndef REFLECTION_H
#define REFLECTION_H

#include <stdbool.h>
#include <stdint.h>


#define REFL_ANNOTATION_GENERAL 0x8000

enum refl_annotation_type
{
    REFL_ANNOTATION_FUNCSIG_PAR_TYPE = REFL_ANNOTATION_GENERAL,
    REFL_ANNOTATION_FUNCSIG_RET_TYPE = REFL_ANNOTATION_GENERAL + 0x10
};

typedef uintptr_t func_t;

struct refl_annotation
{
    func_t func;
    enum refl_annotation_type type;
    const char *data;
};


#define single_instance __attribute__((noinline, noclone))

#define refl_foreach(func) \
    for (func_t func = 0; refl_each_next(&func);)

#define refl_foreach_annotation(func, anno) \
    for (const struct refl_annotation *anno = NULL; refl_each_annotation_next(func, &anno);)

#ifndef __glue
#define __glue(x, y) x ## y
#endif

#define __annotate(afunc, atype, adata, c) \
    static const struct refl_annotation *__glue(__annotation, c) __attribute__((used, section("refl_annotations"))) = &(const struct refl_annotation){ \
        .func = (func_t)(afunc), \
        .type = (atype), \
        .data = (adata) \
    }

#define refl_annotate(afunc, atype, adata) __annotate(afunc, atype, adata, __COUNTER__)


#define refl_dcall(func, ret_type, ...) ((ret_type (*)())func)(__VA_ARGS__)


bool refl_is_virtual(func_t func);
void refl_assign(func_t dest, func_t src);
func_t refl_find(const char *name);
const char *refl_get_name(func_t func);
func_t refl_get_target(func_t func);
bool refl_each_next(func_t *fptr);
const char *refl_get_annotation(func_t func, enum refl_annotation_type type);
bool refl_each_annotation_next(func_t func, const struct refl_annotation **anno);
void refl_call(func_t func, ...);
void refl_call_verify(func_t func, const char *expsig, ...);
void refl_call_sig(func_t func, const char *sig, ...);

#endif
