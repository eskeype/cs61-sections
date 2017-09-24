#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
static int exit_status = 0;

struct node {
    int data;
    struct node* next;
};

extern struct node* traverse(struct node* n);

struct node* baseline_traverse(struct node* n) {
    if (!n) {
        return n;
    }
    while (n->next) {
        n =  n->next;
    }
    return n;
}

static void test_traverse(int n) {
    struct node** nodes = malloc(n * sizeof(struct node*));
    for (int i = 0; i < n; ++i) {
        nodes[i] = malloc(sizeof(struct node));
        nodes[i]->data = 0xdeadbeef;
        nodes[i]->next = NULL;

        if (i > 0) {
            nodes[i-1]->next = nodes[i];
        }
    }

    struct node* baseline = baseline_traverse(nodes[0]);
    struct node* test = traverse(nodes[0]);

    if (test == baseline) {
        printf("traverse(%d) = %p\n", n, test);
    } else {
        printf("ERROR: traverse(%d) = %p, expected %p\n",
               n, test, baseline);
        exit_status = 1;
    }

    for (int i = 0; i < n; ++i) {
        free(nodes[i]);
    }
    free(nodes);
}

int main(void) {
    test_traverse(0);
    test_traverse(1);
    test_traverse(8);
    test_traverse(64);
    test_traverse(255);
    test_traverse(512);
    return exit_status;
}
