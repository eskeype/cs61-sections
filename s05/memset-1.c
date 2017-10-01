#include <stdlib.h>

char* my_memset(char* ptr, char ch, size_t lg_sz) {
  for (size_t i = 0; i < (1ULL << lg_sz); i++) {
    ptr[i] = ch;
  }

  return ptr;
}
