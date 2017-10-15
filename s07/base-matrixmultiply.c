#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <getopt.h>
#include <assert.h>
#include <time.h>

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + 1e-9 * ts.tv_nsec;
}


// me(m, sz, i, j)
//    Return a pointer to matrix element `m[i][j]` -- the element
//    at row `i` and column `j`. The matrix is square with dimension
//    `sz`. Requires: `i < sz && j < sz`
static inline double* me(double* m, size_t sz, size_t i, size_t j) {
    return &m[i * sz + j];
}

// matrix_multiply(c, sz, a, b)
//    `a`, `b`, and `c` are square matrices with dimension `sz`.
//    Computes the matrix product `a x b` and stores it in `c`.
void matrix_multiply(double* c, size_t sz, double* a, double* b) {
    // clear `c`
    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            *me(c, sz, i, j) = 0;
        }
    }

    // compute product and update `c`
    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            for (size_t k = 0; k < sz; ++k) {
                *me(c, sz, i, j) += *me(a, sz, i, k) * *me(b, sz, k, j);
            }
        }
    }
}


// xrandom()
//    Return a pseudo-random number in the range [0, XRAND_MAX].
//    We use our own generator to ensure values computed on different
//    OSes will follow the same sequence.
#define XRAND_MAX 0x7FFFFFFF
static uint64_t xrandom_seed;
unsigned xrandom() {
    xrandom_seed = xrandom_seed * 6364136223846793005U + 1U;
    return (xrandom_seed >> 32) & XRAND_MAX;
}

typedef struct matrix_statistics {
    double corner[4];
    double diagonal_sum;
} matrix_statistics;

// compute_statistics(m, sz)
//    Compute and return some statistics about matrix `m`.
matrix_statistics compute_statistics(double* m, size_t sz) {
    matrix_statistics mstat;
    mstat.corner[0] = *me(m, sz, 0, 0);
    mstat.corner[1] = *me(m, sz, 0, sz-1);
    mstat.corner[2] = *me(m, sz, sz-1, 0);
    mstat.corner[3] = *me(m, sz, sz-1, sz-1);
    mstat.diagonal_sum = 0;
    for (size_t i = 0; i < sz; ++i) {
        mstat.diagonal_sum += *me(m, sz, i, i);
    }
    return mstat;
}

int main(int argc, char* argv[]) {
    size_t sz = 1000;
    int has_seed = 0;

    // read options
    int opt;
    while ((opt = getopt(argc, argv, "n:d:")) != -1) {
        switch (opt) {
        case 'n':
            sz = strtoul(optarg, NULL, 0);
            break;
        case 'd':
            xrandom_seed = strtoul(optarg, NULL, 0);
            has_seed = 1;
            break;
        default:
            fprintf(stderr, "Usage: ./base-matrixmultiply [-n SIZE] [-d SEED]\n");
            exit(EXIT_FAILURE);
        }
    }

    assert(sz > 0);
    assert(sz < (size_t) sqrt(SIZE_MAX / sizeof(double)));
    if (!has_seed) {
        union { double d; uint64_t x; } u;
        u.d = get_time();
        xrandom_seed = u.x;
    }
    printf("size %zu, seed %" PRIu64 "\n", sz, xrandom_seed);

    // allocate matrices
    double* a = (double*) malloc(sizeof(double) * sz * sz);
    double* b = (double*) malloc(sizeof(double) * sz * sz);
    double* c = (double*) malloc(sizeof(double) * sz * sz);

    // fill in source matrices
    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            *me(a, sz, i, j) = xrandom() / (double) XRAND_MAX;
        }
    }

    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            *me(b, sz, i, j) = xrandom() / (double) XRAND_MAX;
        }
    }

    // compute `c = a x b`
    double t0 = get_time();
    matrix_multiply(c, sz, a, b);
    double t1 = get_time();
    matrix_statistics mstat = compute_statistics(c, sz);

    // compute times, print times and ratio
    printf("multiply time %.09f\n", t1 - t0);

    // print statistics and differences
    for (int i = 0; i < 4; ++i) {
        printf("corner statistic %d: %g (%a)\n",
               i, mstat.corner[i], mstat.corner[i]);
    }
    printf("diagonal sum statistic: %g (%a)\n",
           mstat.diagonal_sum, mstat.diagonal_sum);

    free(a);
    free(b);
    free(c);
}
