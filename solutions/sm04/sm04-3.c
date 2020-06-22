#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>


FPClass fpclassf(float value, int *psign) {
    /* wikipedia.org/wiki/Число_одинарной_точности */
    union {
        float    fl;
        uint32_t bits;
    } f;
    f.fl = value;
    
    uint32_t sign = (f.bits >> 31) ? 1 : 0;
    uint32_t exponent = (f.bits >> 23) & 0xff; // aka order
    uint32_t fraction = f.bits & 0x7fffff; // aka mantissa
    
    /* Summary table at steve.hollasch.net/cgindex/coding/ieeefloat.html */
    if (exponent == 0xff && fraction != 0) {
        *psign = 0;
        return FFP_NAN;
    }
    
    *psign = (int) sign;
    
    if (exponent == 0xff && fraction == 0) {
        return FFP_INF;
    }
    
    if (exponent == 0 && fraction == 0) {
        return FFP_ZERO;
    }
    
    if (exponent == 0 && fraction != 0) {
        return FFP_DENORMALIZED;
    }
    
    return FFP_NORMALIZED;
}
