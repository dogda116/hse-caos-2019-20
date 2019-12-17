#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

int bitcount(STYPE value) {
    UTYPE unsgn_val = value;
    int count = 0;
    while (unsgn_val) {
        // increment counter if last bit equals 1
        count += unsgn_val & 1;
        // "new" last bit
        unsgn_val = unsgn_val >> 1;
    }
    return count;
}
