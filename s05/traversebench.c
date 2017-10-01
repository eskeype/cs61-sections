#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRAVERSE_ARRAY              0
#define TRAVERSE_LIST               1

const char* traverse_names[] = {
    "array", "list", NULL
};

double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + 1e-9 * ts.tv_nsec;
}


typedef struct node node;
struct node {
    size_t value;
    node* next;
    size_t other_info[14];
};

node* make_list(size_t n) {
    node** ns = (node**) malloc(n * (sizeof *ns));
    for (size_t i = 0; i < n; ++i) {
        ns[i] = (node*) malloc(sizeof *ns[i]);
        ns[i]->value = i;
        ns[i]->next = NULL;
    }

    node* first = ns[0];
    for (size_t i = 0; i < n - 1; ++i) {
        ns[i]->next = ns[i + 1];
    }

    free(ns);
    return first;
}

node* make_array(size_t n) {
    node* ns = (node*) malloc(n * (sizeof *ns));
    for (size_t i = 0; i < n; ++i) {
        ns[i].value = i;
        ns[i].next = i < n - 1 ? &ns[i + 1] : NULL;
    }
    return ns;
}

inline size_t expensive_sum(size_t value) {
    size_t sum = value;
    sum %= value + 1;
    sum %= value + 2;
    sum %= value + 3;
    sum %= value + 4;
    sum %= value + 5;
    sum %= value + 6;
    sum %= value + 7;
    sum %= value + 8;
    return sum;
}

size_t traverse_and_sum(node* ns, bool prefetch) {
    size_t sum = 0;
    while (ns != NULL) {
        if (prefetch) {
            __asm__ volatile ("prefetch %0" : : "m" (*ns->next));
        }
        sum += expensive_sum(ns->value);
        ns = ns->next;
    }
    return sum;
}

int main(int argc, char** argv) {
    size_t n = 10000000;
    bool prefetch = false;
    int type = TRAVERSE_LIST;

    int opt;
    while (-1 != (opt = getopt(argc, argv, "n:p:t:"))) {
        switch (opt) {
        case 'n':
            n = strtoul(optarg, NULL, 0);
            break;
        case 'p':
            prefetch = !!strtoul(optarg, NULL, 0);
            break;
        case 't':
            for (type = 0; ; ++type) {
                if (!traverse_names[type]) {
                    goto badarg;
                }
                if (strcmp(optarg, traverse_names[type]) == 0
                    || (isdigit((unsigned char) optarg[0])
                        && strtol(optarg, NULL, 0) == type)) {
                    break;
                }
            }
            break;
        default:
        badarg:
            fprintf(stderr, "Usage: ./traversebench "
                "[-n NOPS] [-p PREFETCH[0 | 1]] [-t TYPE]\n");
            exit(EXIT_FAILURE);
        }
    }

    node* ns;

    switch (type) {
    case TRAVERSE_ARRAY:
        ns = make_array(n);
        printf("%zu elements created, array-style\n", n);
        break;
    default:
    case TRAVERSE_LIST:
        ns = make_list(n);
        printf("%zu elements created, list-style\n", n);
        break;
    }

    printf("Traversing with%s prefetching\n", prefetch ? "" : "out");

    double start = get_time();
    size_t sum = traverse_and_sum(ns, prefetch);
    printf("Final sum: %zu, time: %.06f seconds\n", sum, get_time() - start);
}
