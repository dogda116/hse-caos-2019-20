#include <ctype.h>
#include <stdio.h>

int main(void) {
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);
    printf("%*c", n, ' ');
    for (int i = a; i != b; i++) {
        printf(" %*d", n, i);
    }
    printf("\n");
    for (int i = a; i != b; i++) {
        printf("%*d", n, i);
        for (int j = a; j != b; j++) {
            long product = 0;
            product = (long) i * j;
            printf(" %*ld", n, product);
        }
        printf("\n");
    }
    return 0;
}
