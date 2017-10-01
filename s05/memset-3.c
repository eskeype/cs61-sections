#include <stdlib.h>

char* my_memset(char* ptr, char ch, size_t lg_sz) {
  size_t val = 0x0101010101010101UL * ch;
  for (size_t i = 0; i < (1ULL << lg_sz); i += 8) {
    *((size_t*)(ptr + i)) = val;
  }

  return ptr;
}
