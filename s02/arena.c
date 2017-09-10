#include "membench.h"
#include <stdlib.h>
#include <assert.h>


// A `free_chunk` was allocated by the arena, but isn't currently in
// use. You'll likely put some bookkeeping information into such chunks.
typedef struct free_space {
    // YOUR CODE HERE
} free_space;

// An `allocation` object is *either* a chunk (an active allocation),
// *or* a `free_space` object.
typedef union chunk_space {
    chunk active;
    free_space free;
} chunk_space;

// An `arena_group` object contains 1024 `chunk_space` objects.
// Objects `[0, nused)` have been allocated; objects `[nused, 1024)`
// have never been allocated.
#define NSPACES 1024
typedef struct arena_group {
    int nused;
    chunk_space data[NSPACES];
    struct arena_group* next;
} arena_group;

// A `membench_arena` is a singly-linked list of groups.
struct membench_arena {
    arena_group* groups;
};


membench_arena* membench_arena_create(void) {
    membench_arena* arena = (membench_arena*) malloc(sizeof(membench_arena));
    arena->groups = NULL;
    return arena;
}


// group_create(arena)
//    Allocate a new arena_group and append it to the arena->groups list.
//    Return the new group.
static arena_group* group_create(membench_arena* arena) {
    arena_group* g = (arena_group*) malloc(sizeof(arena_group));
    g->nused = 0;
    g->next = NULL;

    // Append `g` to the end of the groups list.
    arena_group* prev = arena->groups;
    while (prev && prev->next != NULL) {
        prev = prev->next;
    }
    if (!prev) {
        arena->groups = g;
    } else {
        prev->next = g;
    }
    return g;
}


chunk* membench_alloc(membench_arena* arena) {
    // Find a group that has free space.
    arena_group* g = arena->groups;
    while (g && g->nused < NSPACES) {
        g = g->next;
    }

    // If we there's no such group, allocate a new one.
    if (!g) {
        g = group_create(arena);
        assert(g && g->nused < NSPACES);
    }

    chunk* result = &g->data[g->nused].active;
    ++g->nused;
    return result;
}


void membench_free(membench_arena* arena, chunk* x) {
    (void) arena, (void) x;
}


void membench_arena_destroy(membench_arena* arena) {
    while (arena->groups != NULL) {
        arena_group* g = arena->groups;
        arena->groups = g->next;
        free(g);
    }
    free(arena);
}
