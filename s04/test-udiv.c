#include <stdio.h>
#include <limits.h>
static int exit_status = 0;

extern unsigned long udiv(unsigned long n);

unsigned long baseline_udiv(unsigned long n) {
    return n / 1024;
}

static void test_udiv(unsigned long n) {
    unsigned long baseline = baseline_udiv(n);
    unsigned long test = udiv(n);
    if (test == baseline) {
        printf("udiv(%lu) = %lu\n", n, test);
    } else {
        printf("ERROR: udiv(%lu) = %lu, expected %lu\n",
               n, test, baseline);
        exit_status = 1;
    }
}

int main(void) {
    test_udiv(0);
    test_udiv(1023);
    test_udiv(1024);
    test_udiv(1UL << 36);
    test_udiv(ULONG_MAX);
    return exit_status;
}
