#include <stdlib.h>

char* my_memset(char* ptr, char ch, size_t lg_sz) {
  for (size_t i = 0; i < (1ULL << lg_sz); i += 8) {
    ptr[i] = ch;
    ptr[i + 1] = ch;
    ptr[i + 2] = ch;
    ptr[i + 3] = ch;
    ptr[i + 4] = ch;
    ptr[i + 5] = ch;
    ptr[i + 6] = ch;
    ptr[i + 7] = ch;
  }

  return ptr;
}
