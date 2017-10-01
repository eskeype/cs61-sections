#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memsetbench.h"

#define MEMSET_LIBC                 0
#define MEMSET_BASIC                1
#define MEMSET_UNROLLED             2
#define MEMSET_WORDWISE             3
#define MEMSET_WORDWISE_UNROLLED    4

const char* memset_names[] = {
    "libc", "basic", "unrolled", "wordwise", "wordwise_unrolled", NULL
};

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + 1e-9 * ts.tv_nsec;
}

int main(int argc, char** argv) {
    size_t n = 10000000;
    size_t runs = 128;
    int type = MEMSET_BASIC;

    int opt;
    while ((opt = getopt(argc, argv, "n:t:r:")) != -1) {
        switch (opt) {
        case 'n':
            n = strtoul(optarg, NULL, 0);
            break;
        case 'r':
            runs = strtoul(optarg, NULL, 0);
            break;
        case 't':
            for (type = 0; ; ++type) {
                if (!memset_names[type]) {
                    goto badarg;
                }
                if (strcmp(optarg, memset_names[type]) == 0
                    || (isdigit((unsigned char) optarg[0])
                        && strtol(optarg, NULL, 0) == type)) {
                    break;
                }
            }
            break;
        default:
        badarg:
            fprintf(stderr, "Usage: ./memsetbench [-n NOPS] [-t TYPE]\n");
            exit(EXIT_FAILURE);
        }
    }

    char* array = (char*) malloc(n);

    double time = 0;
    size_t runi;
    for (runi = 0; runi < runs || time < 0.125; ++runi) {
        double t0 = get_time();
        switch (type) {
        case MEMSET_LIBC:
            memset(array, 61 + runi, n);
            break;
        case MEMSET_BASIC:
            memset_basic(array, 61 + runi, n);
            break;
        case MEMSET_UNROLLED:
            memset_unrolled(array, 61 + runi, n);
            break;
        case MEMSET_WORDWISE:
            memset_wordwise(array, 61 + runi, n);
            break;
        case MEMSET_WORDWISE_UNROLLED:
            memset_wordwise_unrolled(array, 61 + runi, n);
            break;
        }
        time += get_time() - t0;
    }

    printf("memset type: %s; array size: %zu\n", memset_names[type], n);
    printf("Average time over %zu runs: %.06f microseconds/run\n",
           runi, 1e6 * time / runi);
}
