#include <stdio.h>
#include <sys/time.h>

#define RUNS 1000000ULL
#define LG_SZ 6

char* my_memset(char* ptr, char ch, size_t sz);

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + 1e-6 * tv.tv_usec;
}

int main() {
  char array[1 << LG_SZ];
  char ch[4] = {'C', 'S', '6', '1'};

  double total_time = 0;
  double start;
  size_t tests = (sizeof ch);
  for (size_t i = 0; i < RUNS; i++) {
    for (size_t j = 0; j < tests; j++) {
      start = get_time();
      my_memset(array, ch[j], LG_SZ);
      total_time += get_time() - start;
    }
  }

  printf("Average time over %llu runs: %.6lf microseconds\n",
    RUNS, 1e6 * total_time / RUNS);
}
