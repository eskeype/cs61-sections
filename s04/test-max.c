#include <stdio.h>
#include <limits.h>
static int exit_status = 0;

extern int max(int a, int b);

int baseline_max(int a, int b) {
    return a > b ? a : b;
}

static void test_max(int a, int b) {
    int baseline = baseline_max(a, b);
    int test = max(a, b);
    if (test == baseline) {
        printf("max(%d, %d) = %d\n", a, b, test);
    } else {
        printf("ERROR: max(%d, %d) = %d, expected %d\n",
               a, b, test, baseline);
        exit_status = 1;
    }
}

int main(void) {
    test_max(1, 0);
    test_max(-1, 1);
    test_max(0, 0xffffffff);
    test_max(0xf0000000, 0x8fffffff);
    test_max(0xdeadbeef, 0xdeadbeef);
    return exit_status;
}

