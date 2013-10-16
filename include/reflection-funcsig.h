#ifndef REFLECTION_FUNCSIG_H
#define REFLECTION_FUNCSIG_H

#include "reflection.h"
#include "reflection-typestr.h"
#include "p99/p99.h"

#define __do_type(name, x, i) refl_annotate(name, REFL_ANNOTATION_FUNCSIG_PAR_TYPE + i, typestr(x))

#define refl_generate(ret, func, ...) \
    ret func(__VA_ARGS__) single_instance; \
    refl_annotate(func, REFL_ANNOTATION_FUNCSIG_RET_TYPE, typestr(ret)); \
    P99_FOR(func, P99_NARG(__VA_ARGS__), P00_SEP, __do_type, __VA_ARGS__)

#endif
