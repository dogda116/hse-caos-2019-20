#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>

int main(void) {
    setlocale(LC_ALL, "");
    long long lowercase = 0, uppercase = 0, digit = 0;
    wchar_t chr;
    while ((chr = fgetwc(stdin)) != EOF) {
        lowercase += (iswlower(chr) != 0);
        uppercase += (iswupper(chr) != 0);
        digit += (iswdigit(chr) != 0);
    }
    printf("%lld\n%lld\n%lld\n", digit, uppercase, lowercase);
    return 0;
}
