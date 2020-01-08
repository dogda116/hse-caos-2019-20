#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

void normalize_path(char *buf) {
    char *first = buf;
    char *second = buf;
    bool first_slash = true;

    while (*first != '\0') {
        if (*first == '/') {
            if (first_slash) {
                *second = *first;
                ++first;
                ++second;
                first_slash = false;
            } else {
                ++first;
            }
        } else {
            *second = *first;
            ++first;
            ++second;
            first_slash = true;
        }
    }
    *second = '\0';
}
