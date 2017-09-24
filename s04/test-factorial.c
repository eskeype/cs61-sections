#include <stdio.h>
#include <limits.h>
static int exit_status = 0;

extern unsigned long factorial(unsigned long n);

unsigned long baseline_factorial(unsigned long n) {
    if (n <= 1) {
        return 1;
    }
    return n * baseline_factorial(n - 1);
}

static void test_factorial(unsigned long n) {
    unsigned long baseline = baseline_factorial(n);
    unsigned long test = factorial(n);
    if (test == baseline) {
        printf("factorial(%lu) = %lu\n", n, test);
    } else {
        printf("ERROR: factorial(%lu) = %lu, expected %lu\n",
               n, test, baseline);
        exit_status = 1;
    }
}

int main(void) {
    test_factorial(0);
    test_factorial(1);
    test_factorial(3);
    test_factorial(6);
    test_factorial(10);
    return exit_status;
}
