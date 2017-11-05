#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
  int file;
  char c;
  file = open("alphabet.txt", O_RDONLY);

  if (file <= 0) {
    printf("Could not open file.\n");
    return 1;
  }

  // read (and ignore) first byte of file
  read(file, &c, 1);
  
  pid_t pid;
  pid = fork();

  if (pid < 0)
  {
    perror("Could not fork\n");
  }
  else if (pid == 0)
  {
    // This is the Child Process
    read(file, &c, 1);
    printf("Child: %c\n", c);
  }
  else
  {
    // This is the parent process
    read(file, &c, 1);
    printf("Parent: %c\n", c);
  }
  
  return 0;
}
