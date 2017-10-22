#include <stdio.h>
#include <stdlib.h>
int increment(int arg1){
    int b;
    asm("movl %1, %%eax;\n\t"
        "addl $1, %%eax;\n\t"
        "movl %%eax, %0;\n\t"
        :"=r"(b)           /* output */
        :"r"(arg1)         /* input */
        :"%eax"            /* this register changed! */
       );
    return b;
}

int increment_short(int arg1){
    int b;
    asm("addl $1, %1;\n\t"
        "movl %1, %0;\n\t"
        :"=r"(b)           /* output */
        :"r"(arg1)         /* input */
       );
    return b;
}

int increment_register(int arg1){
    int b = 0;
    asm("addl $1, %1;\n\t"
        "movl %1, %0;\n\t"
        :"=a"(b)           /* output */
        :"b"(arg1)         /* input */
       );
    return b;
}

int main (int argc, char * argv[]) {
    printf("%d\n", increment(1));
    printf("%d\n", increment_short(3));
    return 0;
}
