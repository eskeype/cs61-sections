#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: %s program-name\n", argv[0]);
    exit(1);
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("Could not fork!\n");
  }
  else if (pid == 0) { 
    // child process
    char *child_argv[] = {argv[1], NULL};
    execvp(argv[1], child_argv); // does not return on success
    perror("Couldn’t execute program!\n");
  } 
  else { 
    // parent process
    waitpid(pid, NULL, 0);
    printf("done\n");
  }
}
