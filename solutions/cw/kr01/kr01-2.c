#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>


int main() {
    int next_char;
    int curr = 0;
    int res = 0;
    int has_q = 0;
    while ((next_char = getchar_unlocked()) != EOF) {
        if (islower(next_char) != 0) {            
            if (has_q) continue;
            if (next_char == 'q') {
                has_q = 1;
                curr = 0;
                continue;
            }
            ++curr;
        } else {
            if (!has_q) {
                if (curr > res) {
                    res = curr;
                }
            }
            has_q = 0;
            curr = 0;
        }
    }
    if (!has_q) {
        if (curr > res) {
            res = curr;
        }
    }
    printf("%d\n", res);
    return 0;
}
