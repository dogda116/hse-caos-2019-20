#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>

typedef double (*funcptr_t) (double a);

typedef struct FunctionTable
{
    char * f_name;
    funcptr_t function;
} FuncTable;

static const FuncTable f_table[] = {
        { "sqrt", &sqrt },
        { "tan", &tan },
        { "log", &log },
        { "exp", &exp },
        { "cos", &cos },
        { "sin", &sin }
};

int main(void) {
    double input_number;
    char f_name[1000001];
    while (scanf("%s %lg", f_name, &input_number) == 2) {
        bool function_in_table = false;
        for (size_t i = 0; i != sizeof(f_table) / sizeof(FuncTable); ++i) {
            if (!strcmp(f_table[i].f_name, f_name)) {
                function_in_table = true;
                printf("%a\n", f_table[i].function(input_number));
                break;
            }
        }

        if (!function_in_table)
            printf("%a\n", NAN);
    }
    return 0;
}
