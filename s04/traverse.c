//! -O0

struct node {
    int data;
    struct node* next;
};

// returns a pointer to the last node in a linked list
struct node* traverse(struct node* n) {
    if (!n) {
        return n;
    }
    while (n->next) {
        n = n->next;
    }
    return n;
}
