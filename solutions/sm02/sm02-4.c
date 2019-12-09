#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(void) {
    bool conditions[2] = {false, false};
    int next_char = getchar_unlocked();
    double parts[3] = {0, 0, 1.0 / 7};
    char point = '.';
    while (next_char != -1) {
        if (next_char == point) {
            next_char = getchar_unlocked();
            conditions[1] = true;
        } else if (next_char != point && !isdigit(next_char)) {
            if (conditions[0]) {
                printf("%.10g\n", parts[0] + parts[1]);
                parts[2] = 1.0 / 7;
                parts[1] = 0;
                parts[0] = 0;
                conditions[0] = false;
                conditions[1] = false;
            }
            next_char = getchar_unlocked();
        } else {
            if (conditions[1]) {
                parts[1] += (next_char - '0') * parts[2];
                parts[2] /= 7;
            } else {
                parts[0] = parts[0] * 7 + (next_char - '0');
            }
            next_char = getchar_unlocked();
            conditions[0] = true;
        }
    }
    if (conditions[0]) {
        printf("%.10g\n", parts[0] + parts[1]);
    }
    return 0;
}
