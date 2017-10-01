#include <stddef.h>

void* memset_basic(void* s, int c, size_t n);
void* memset_unrolled(void* s, int c, size_t n);
void* memset_wordwise(void* s, int c, size_t n);
void* memset_wordwise_unrolled(void* s, int c, size_t n);
