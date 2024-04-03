#include <stdint.h>
#include <float.h>
#include <math.h>

#define FORCE_EVAL(x)                            \
    do {                                         \
        if(sizeof(x) == sizeof(float)) {         \
            volatile float __x;                  \
            __x = (x);                           \
            (void)__x;                           \
        } else if(sizeof(x) == sizeof(double)) { \
            volatile double __x;                 \
            __x = (x);                           \
            (void)__x;                           \
        } else {                                 \
            volatile long double __x;            \
            __x = (x);                           \
            (void)__x;                           \
        }                                        \
    } while(0)

float floorf(float x) {
    union {
        float f;
        uint32_t i;
    } u = {x};
    int e = (int)(u.i >> 23 & 0xff) - 0x7f;
    uint32_t m;

    if(e >= 23) return x;
    if(e >= 0) {
        m = 0x007fffff >> e;
        if((u.i & m) == 0) return x;
        FORCE_EVAL(x + 0x1p120f);
        if(u.i >> 31) u.i += m;
        u.i &= ~m;
    } else {
        FORCE_EVAL(x + 0x1p120f);
        if(u.i >> 31 == 0)
            u.i = 0;
        else if(u.i << 1)
            u.f = -1.0;
    }
    return u.f;
}

float fmodf(float x, float y) {
    union {
        float f;
        uint32_t i;
    } ux = {x}, uy = {y};
    int ex = ux.i >> 23 & 0xff;
    int ey = uy.i >> 23 & 0xff;
    uint32_t sx = ux.i & 0x80000000;
    uint32_t i;
    uint32_t uxi = ux.i;

    if(uy.i << 1 == 0 || isnan(y) || ex == 0xff) return (x * y) / (x * y);
    if(uxi << 1 <= uy.i << 1) {
        if(uxi << 1 == uy.i << 1) return 0 * x;
        return x;
    }

    /* normalize x and y */
    if(!ex) {
        for(i = uxi << 9; i >> 31 == 0; ex--, i <<= 1)
            ;
        uxi <<= -ex + 1;
    } else {
        uxi &= -1U >> 9;
        uxi |= 1U << 23;
    }
    if(!ey) {
        for(i = uy.i << 9; i >> 31 == 0; ey--, i <<= 1)
            ;
        uy.i <<= -ey + 1;
    } else {
        uy.i &= -1U >> 9;
        uy.i |= 1U << 23;
    }

    /* x mod y */
    for(; ex > ey; ex--) {
        i = uxi - uy.i;
        if(i >> 31 == 0) {
            if(i == 0) return 0 * x;
            uxi = i;
        }
        uxi <<= 1;
    }
    i = uxi - uy.i;
    if(i >> 31 == 0) {
        if(i == 0) return 0 * x;
        uxi = i;
    }
    for(; uxi >> 23 == 0; uxi <<= 1, ex--)
        ;

    /* scale result up */
    if(ex > 0) {
        uxi -= 1U << 23;
        uxi |= (uint32_t)ex << 23;
    } else {
        uxi >>= -ex + 1;
    }
    uxi |= sx;
    ux.i = uxi;
    return ux.f;
}

float nearbyintf(float x) {
    union {
        float f;
        uint32_t i;
    } u = {x};
    int e = u.i >> 23 & 0xff;
    int s = u.i >> 31;
    float_t y;

    if(e >= 0x7f + 23) return x;
    if(s)
        y = x - 0x1p23f + 0x1p23f;
    else
        y = x + 0x1p23f - 0x1p23f;
    if(y == 0) return s ? -0.0f : 0.0f;
    return y;
}

//
// __aebi_x2x functions are just here to prevent compiler warnings
//
double __aeabi_i2d(int x) {
    return (double)x;
}

float __aeabi_d2f(double x) {
    return (float)x;
}

double __aeabi_f2d(float x) {
    return (double)x;
}
