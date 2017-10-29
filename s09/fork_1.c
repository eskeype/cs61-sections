#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Parent pid: %d\n", getpid());

    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("We must be in the child because pid is %d!\n", pid);
    } else {
        printf("Return value from fork: %d\n", pid);
    }

    return 0;
}
