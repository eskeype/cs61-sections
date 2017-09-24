//! -O0

void swap(int* a, int* b, unsigned long n) {
    if (!a || !b) {
        return;
    }

    int temp = 0;
    for (unsigned long i = 0; i < n; ++i) {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
