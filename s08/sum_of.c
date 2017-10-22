#include <stdarg.h>
#include <assert.h>
#include <stdio.h>

int sum_of(int n, ...) {
    va_list va;
    va_start(va, n);   // initialize `va`; varargs start after argument `n`
    int sum = 0;
    for (int i = 0; i != n; ++i) {
        int arg = va_arg(va, int);     // pop the next variable argument,
                                       // which has type `int`
        sum += arg;
    }
    va_end(va);
    return sum;
}

int main(void) {
    printf("sum_of(0) = %d\n", sum_of(0));
    printf("sum_of(1, 1) = %d\n", sum_of(1, 1));
    printf("sum_of(1, 1, 2, 3) = %d\n", sum_of(1, 1, 2, 3));
    printf("sum_of(3, 1, 2, 3) = %d\n", sum_of(3, 1, 2, 3));
    return 0;
}
