#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


/// spec_size(spec)
///    Return the size of the C struct specified by the type specification `spec`,
///    as compiled on an x86-64 machine. A type specification is a string of
///    characters where each character corresponds to a struct member of some
///    fundamental type:
///
///         `c`    char (or signed char, unsigned char)
///         `s`    short (or unsigned short)
///         `i`    int (or unsigned int)
///         `l`    long (or unsigned long)
///         `z`    size_t
///         `f`    float
///         `d`    double
///         `p`    pointer
///
///    See `README.md` or the Section 1 wiki page for hints and advanced features.

size_t spec_size(const char* spec) {
    (void) spec;
    // YOUR CODE HERE
    return 0;
}


/// spec_print(spec, ptr)
///    Print the contents of the memory located at `ptr` as interpreted
///    by type specification `spec`. For example:
///
///        int i = 10;
///        spec_print("i", &i);
///
///    might print something like
///
///        7fffffabc int 10
///
///    (assuming `i` is located at address 0x7fffffabc), and
///
///        struct { char c; int d; } x = { 'A', 24 };
///        spec_print("ci", &x);
///
///    might print something like
///
///        7ffffffabc char A
///        7ffffffac0 int 24
///
///    You'll need to add your own tests of `spec_print`.

void spec_print(const char* spec, const void* data) {
    (void) spec, (void) data;
    // YOUR CODE HERE
}


int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        printf("%8zu %s\n", spec_size(argv[i]), argv[i]);
    }
}
