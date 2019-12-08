#include <ctype.h>
#include <stdio.h>

int main(void) {
    int result = 0, next_char;
    while ((next_char = getchar_unlocked()) != EOF) {
        if (isdigit(next_char)) {
            result += next_char - '0';
        }
    }
    printf("%d\n", result);
    return 0;
}
