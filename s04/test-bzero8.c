#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern void bzero8(void* ptr, size_t n);

void baseline_bzero8(void* ptr, size_t n) {
    if (n % 8 != 0) {
        return;
    }
    char* b = (char*) ptr;
    for (size_t i = 0; i < n; ++i) {
        b[i] = 0;
    }
}

static void test_bzero8(int n) {
    char* ptr1 = malloc(n + 16);
    assert(ptr1);
    char* ptr2 = malloc(n + 16);
    assert(ptr2);

    memset(ptr1, 42, n + 16);
    memset(ptr2, 42, n + 16);

    bzero8(ptr1 + 8, n);
    baseline_bzero8(ptr2 + 8, n);

    for (int i = 0; i < n + 16; ++i) {
        if (ptr1[i] != ptr2[i]) {
            printf("ERROR: bzero8(%d) got %d at index %d, expected %d\n",
                   n, ptr1[i], i - 8, ptr2[i]);
            return;
        }
    }

    printf("bzero8(%d) passed\n", n);

    free(ptr1);
    free(ptr2);
}

int main(void) {
    test_bzero8(0);
    test_bzero8(1);
    test_bzero8(8);
    test_bzero8(64);
    test_bzero8(255);
    test_bzero8(512);
    return 0;
}
