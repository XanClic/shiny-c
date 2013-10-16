#ifndef REFLECTION_TYPESTR_H
#define REFLECTION_TYPESTR_H
#
#define __typestr_test(t1, t2, n) \
    __builtin_choose_expr(__builtin_types_compatible_p(t1, t2), n,

#define __typestr1(type, ts, sp) \
    __typestr_test(type, char ts, sp "c") \
    __typestr_test(type, signed char ts, sp "a") \
    __typestr_test(type, unsigned char ts, sp "h") \
    __typestr_test(type, short ts, sp "s") \
    __typestr_test(type, unsigned short ts, sp "t") \
    __typestr_test(type, int ts, sp "i") \
    __typestr_test(type, unsigned ts, sp "j") \
    __typestr_test(type, long ts, sp "l") \
    __typestr_test(type, unsigned long ts, sp "m") \
    __typestr_test(type, long long ts, sp "x") \
    __typestr_test(type, unsigned long long ts, sp "y") \
    __typestr_test(type, float ts, sp "f") \
    __typestr_test(type, double ts, sp "d") \
    __typestr_test(type, long double ts, sp "e") \
    __typestr_test(type, void ts, sp "v") \
    __typestr_test(type, volatile char ts, sp "Vc") \
    __typestr_test(type, volatile signed char ts, sp "Va") \
    __typestr_test(type, volatile unsigned char ts, sp "Vh") \
    __typestr_test(type, volatile short ts, sp "Vs") \
    __typestr_test(type, volatile unsigned short ts, sp "Vt") \
    __typestr_test(type, volatile int ts, sp "Vi") \
    __typestr_test(type, volatile unsigned ts, sp "Vj") \
    __typestr_test(type, volatile long ts, sp "Vl") \
    __typestr_test(type, volatile unsigned long ts, sp "Vm") \
    __typestr_test(type, volatile long long ts, sp "Vx") \
    __typestr_test(type, volatile unsigned long long ts, sp "Vy") \
    __typestr_test(type, volatile float ts, sp "Vf") \
    __typestr_test(type, volatile double ts, sp "Vd") \
    __typestr_test(type, volatile long double ts, sp "Ve") \
    __typestr_test(type, volatile void ts, sp "Vv") \
    __typestr_test(type, const char ts, sp "Kc") \
    __typestr_test(type, const signed char ts, sp "Ka") \
    __typestr_test(type, const unsigned char ts, sp "Kh") \
    __typestr_test(type, const short ts, sp "Ks") \
    __typestr_test(type, const unsigned short ts, sp "Kt") \
    __typestr_test(type, const int ts, sp "Ki") \
    __typestr_test(type, const unsigned ts, sp "Kj") \
    __typestr_test(type, const long ts, sp "Kl") \
    __typestr_test(type, const unsigned long ts, sp "Km") \
    __typestr_test(type, const long long ts, sp "Kx") \
    __typestr_test(type, const unsigned long long ts, sp "Ky") \
    __typestr_test(type, const float ts, sp "Kf") \
    __typestr_test(type, const double ts, sp "Kd") \
    __typestr_test(type, const long double ts, sp "Ke") \
    __typestr_test(type, const void ts, sp "Kv") \
    __typestr_test(type, const volatile char ts, sp "KVc") \
    __typestr_test(type, const volatile signed char ts, sp "KVa") \
    __typestr_test(type, const volatile unsigned char ts, sp "KVh") \
    __typestr_test(type, const volatile short ts, sp "KVs") \
    __typestr_test(type, const volatile unsigned short ts, sp "KVt") \
    __typestr_test(type, const volatile int ts, sp "KVi") \
    __typestr_test(type, const volatile unsigned ts, sp "KVj") \
    __typestr_test(type, const volatile long ts, sp "KVl") \
    __typestr_test(type, const volatile unsigned long ts, sp "KVm") \
    __typestr_test(type, const volatile long long ts, sp "KVx") \
    __typestr_test(type, const volatile unsigned long long ts, sp "KVy") \
    __typestr_test(type, const volatile float ts, sp "KVf") \
    __typestr_test(type, const volatile double ts, sp "KVd") \
    __typestr_test(type, const volatile long double ts, sp "KVe") \
    __typestr_test(type, const volatile void ts, sp "KVv") \
    0))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

#define __resolv_test(t1, t2) \
    __builtin_choose_expr(__builtin_types_compatible_p(t1, t2), 1,

#define __resolvable1(type, ts) \
    __resolv_test(type, char ts) \
    __resolv_test(type, signed char ts) \
    __resolv_test(type, unsigned char ts) \
    __resolv_test(type, short ts) \
    __resolv_test(type, unsigned short ts) \
    __resolv_test(type, int ts) \
    __resolv_test(type, unsigned ts) \
    __resolv_test(type, long ts) \
    __resolv_test(type, unsigned long ts) \
    __resolv_test(type, long long ts) \
    __resolv_test(type, unsigned long long ts) \
    __resolv_test(type, float ts) \
    __resolv_test(type, double ts) \
    __resolv_test(type, long double ts) \
    __resolv_test(type, void ts) \
    __resolv_test(type, volatile char ts) \
    __resolv_test(type, volatile signed char ts) \
    __resolv_test(type, volatile unsigned char ts) \
    __resolv_test(type, volatile short ts) \
    __resolv_test(type, volatile unsigned short ts) \
    __resolv_test(type, volatile int ts) \
    __resolv_test(type, volatile unsigned ts) \
    __resolv_test(type, volatile long ts) \
    __resolv_test(type, volatile unsigned long ts) \
    __resolv_test(type, volatile long long ts) \
    __resolv_test(type, volatile unsigned long long ts) \
    __resolv_test(type, volatile float ts) \
    __resolv_test(type, volatile double ts) \
    __resolv_test(type, volatile long double ts) \
    __resolv_test(type, volatile void ts) \
    __resolv_test(type, const char ts) \
    __resolv_test(type, const signed char ts) \
    __resolv_test(type, const unsigned char ts) \
    __resolv_test(type, const short ts) \
    __resolv_test(type, const unsigned short ts) \
    __resolv_test(type, const int ts) \
    __resolv_test(type, const unsigned ts) \
    __resolv_test(type, const long ts) \
    __resolv_test(type, const unsigned long ts) \
    __resolv_test(type, const long long ts) \
    __resolv_test(type, const unsigned long long ts) \
    __resolv_test(type, const float ts) \
    __resolv_test(type, const double ts) \
    __resolv_test(type, const long double ts) \
    __resolv_test(type, const void ts) \
    __resolv_test(type, const volatile char ts) \
    __resolv_test(type, const volatile signed char ts) \
    __resolv_test(type, const volatile unsigned char ts) \
    __resolv_test(type, const volatile short ts) \
    __resolv_test(type, const volatile unsigned short ts) \
    __resolv_test(type, const volatile int ts) \
    __resolv_test(type, const volatile unsigned ts) \
    __resolv_test(type, const volatile long ts) \
    __resolv_test(type, const volatile unsigned long ts) \
    __resolv_test(type, const volatile long long ts) \
    __resolv_test(type, const volatile unsigned long long ts) \
    __resolv_test(type, const volatile float ts) \
    __resolv_test(type, const volatile double ts) \
    __resolv_test(type, const volatile long double ts) \
    __resolv_test(type, const volatile void ts) \
    0))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

#define __typestr2(type, ts, sp) \
    __builtin_choose_expr(__resolvable1(type, ts), __typestr1(type, ts, sp), \
    __builtin_choose_expr(__resolvable1(type, ts const *), __typestr1(type, ts const *, "PK" sp), \
    __builtin_choose_expr(__resolvable1(type, ts volatile *), __typestr1(type, ts volatile *, "PV" sp), \
    __typestr1(type, ts *, "P" sp))))

#define __resolvable2(type, ts) \
    (__resolvable1(type, ts) | \
     __resolvable1(type, ts const *) | \
     __resolvable1(type, ts volatile *) | \
     __resolvable1(type, ts *))

#define __typestr3(type, ts, sp) \
    __builtin_choose_expr(__resolvable2(type, ts), __typestr2(type, ts, sp), \
    __builtin_choose_expr(__resolvable2(type, ts const *), __typestr2(type, ts const *, "PK" sp), \
    __builtin_choose_expr(__resolvable2(type, ts volatile *), __typestr2(type, ts volatile *, "PV" sp), \
    __typestr2(type, ts *, "P" sp))))

#define __resolvable3(type, ts) \
    (__resolvable2(type, ts) | \
     __resolvable2(type, ts const *) | \
     __resolvable2(type, ts volatile *) | \
     __resolvable2(type, ts *))

#define __typestr4(type, ts, sp) \
    __builtin_choose_expr(__resolvable3(type, ts), __typestr3(type, ts, sp), \
    __builtin_choose_expr(__resolvable3(type, ts const *), __typestr3(type, ts const *, "PK" sp), \
    __builtin_choose_expr(__resolvable3(type, ts volatile *), __typestr3(type, ts volatile *, "PV" sp), \
    __typestr3(type, ts *, "P" sp))))

#define __resolvable4(type, ts) \
    (__resolvable3(type, ts) | \
     __resolvable3(type, ts const *) | \
     __resolvable3(type, ts volatile *) | \
     __resolvable3(type, ts *))

#define typestr(type) __typestr4(type,,)
#define resolvable_to_typestr(type) __resolvable4(type,)

#endif
