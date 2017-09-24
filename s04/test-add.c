#include <stdio.h>
static int exit_status = 0;

extern int add(int a, int b);

int baseline_add(int a, int b) {
    return a + b;
}

static void test_add(int a, int b) {
    long baseline = baseline_add(a, b);
    long test = add(a, b);
    if (test == baseline) {
        printf("add(%d, %d) = %ld\n", a, b, test);
    } else {
        printf("ERROR: add(%d, %d) = %ld, expected %ld\n",
               a, b, test, baseline);
        exit_status = 1;
    }
}

int main(void) {
    test_add(0, 0);
    test_add(2, 2);
    test_add(1, -10);
    test_add(0x7FFFFFFF, 8);
    test_add(0x7FFFFFFF, -0x80000000);
    return exit_status;
}
