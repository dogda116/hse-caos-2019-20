#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <inttypes.h>


int main() {
    int sz = 0, a = 0, b = 0, c = 0, d = 0;
    int t;
    while ((t = getchar_unlocked()) != EOF) {
        if (t == '0') {
            if (a == 0) a = sz * 4 + 1;
            b = sz++ * 4 + 4;
        }
        if (t == '1') {
            if (a == 0) a = sz * 4 + 1;
            b = sz++ * 4 + 3;
        }
        if (t == '2') {
            if (a == 0) a = sz * 4 + 1;
            b = sz++ * 4 + 2;
        }
        if (t == '3') {
            if (a == 0) a = sz * 4 + 1;
            b = sz++ * 4 + 2;
        }
        if (t == '4' || t == '5' || t == '6' || t == '7') {
            if (a == 0) a = sz * 4 + 1;
            b = sz++ * 4 + 1;
        }
        if (t == '8') {
            if (a == 0) a = sz * 4 + 2;
            b = sz++ * 4 + 4;
        }
        if (t == '9') {
            if (a == 0) a = sz * 4 + 2;
            b = sz++ * 4 + 3;
        }
        if (t == 'a' || t == 'A' || t == 'b' || t == 'B') {
            if (a == 0) a = sz * 4 + 2;
            b = sz++ * 4 + 2;
        }
        if (t == 'c' || t == 'C') {
            if (a == 0) a = sz * 4 + 3;
            b = sz++ * 4 + 4;
        }
        if (t == 'd' || t == 'D') {
            if (a == 0) a = sz * 4 + 3;
            b = sz++ * 4 + 3;
        }
        if (t == 'e' || t == 'E') {
            if (a == 0) a = sz * 4 + 4;
            b = sz++ * 4 + 4;
        }
        if (t == 'f' || t == 'F') ++sz;
    }
    
    sz = (int) sqrt((double) sz);
    sz *= 2;
    if (a == 0) {
        printf("%d 0 0 0 0\n", sz);
        return 0;
    }
    c = a - (a / sz) * sz - 1;
    a /= sz;
    d = b - (b / sz) * sz - 1;
    b /= sz;
    printf("%d %d %d %d %d\n", sz, a, c, b, d);
    return 0;
}
