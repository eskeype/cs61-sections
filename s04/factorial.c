//! -O0

unsigned long factorial(unsigned long n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
