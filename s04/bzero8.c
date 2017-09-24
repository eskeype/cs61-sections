//! -O0

// zeroes memory regions with length multiple of 8
void bzero8(void* ptr, unsigned long n) {
    if (n % 8 != 0) {
        return;
    }
    char* b = (char*) ptr;
    for (unsigned long i = 0; i < n; ++i) {
        b[i] = 0;
    }
}
