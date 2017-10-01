#include "memsetbench.h"
#include <assert.h>
#include <stdint.h>

void* memset_basic(void* s, int c, size_t n) {
    char* p = (char*) s;
    char* endp = s + n;
    for (; p < endp; ++p) {
        *p = c;
    }
    return s;
}

void* memset_unrolled(void* s, int c, size_t n) {
    assert(n % 8 == 0);
    char* p = (char*) s;
    char* endp = s + n;
    for (; p < endp; p += 8) {
        p[0] = c;
        p[1] = c;
        p[2] = c;
        p[3] = c;
        p[4] = c;
        p[5] = c;
        p[6] = c;
        p[7] = c;
    }
    return s;
}

void* memset_wordwise(void* s, int c, size_t n) {
    assert(n % 8 == 0);
    assert(((uintptr_t) s) % 8 == 0);
    char* p = (char*) s;
    char* endp = s + n;
    unsigned long c8 = 0x0101010101010101UL * ((unsigned char) c);
    for (; p < endp; p += 8) {
        *((unsigned long*) p) = c8;
    }
    return s;
}

void* memset_wordwise_unrolled(void* s, int c, size_t n) {
    assert(n % 64 == 0);
    assert(((uintptr_t) s) % 8 == 0);
    char* p = (char*) s;
    char* endp = s + n;
    unsigned long c8 = 0x0101010101010101UL * ((unsigned char) c);
    for (; p < endp; p += 64) {
        ((unsigned long*) p)[0] = c8;
        ((unsigned long*) p)[1] = c8;
        ((unsigned long*) p)[2] = c8;
        ((unsigned long*) p)[3] = c8;
        ((unsigned long*) p)[4] = c8;
        ((unsigned long*) p)[5] = c8;
        ((unsigned long*) p)[6] = c8;
        ((unsigned long*) p)[7] = c8;
    }
    return s;
}
