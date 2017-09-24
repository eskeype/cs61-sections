#include <stdio.h>
#include <limits.h>

extern void swap(int* a, int* b, unsigned long n);

void baseline_swap(int* a, int* b, unsigned long n) {
    if (!a || !b) {
        return;
    }

    int temp = 0;
    for (unsigned long i = 0; i < n; i++) {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

static void test_swap(int* a, int* b,
                      int* c, int* d, unsigned long n) {
    swap(a, b, n);
    baseline_swap(c, d, n);

    for (unsigned long i = 0; i < n; i++) {
        if (a && c && a[i] != c[i]) {
            printf("ERROR: swap(%p, %p, %lu) got %d at aindex %lu, expected %d\n",
                   a, b, n, a[i], i, c[i]);
            return;
        }
        if (b && d && b[i] != d[i]) {
            printf("ERROR: swap(%p, %p, %lu) got %d at bindex %lu, expected %d\n",
                   a, b, n, b[i], i, d[i]);
            return;
        }
    }
    printf("swap(%p, %p, %lu) passed\n", a, b, n);
}

int main(void) {
    int a[4] = {0, 1, 2, 3};
    int b[4] = {42, 666, 0xdeadbeef, 0xd15ea5e};
    int c[4] = {0, 1, 2, 3};
    int d[4] = {42, 666, 0xdeadbeef, 0xd15ea5e};

    test_swap(a, b, c, d, 1);
    test_swap(a, b, c, d, 4);
    test_swap(NULL, b, NULL, d, 1);
    test_swap(a, NULL, c, NULL, 1);
    test_swap(b, b, d, d, 4);

    return 0;
}
