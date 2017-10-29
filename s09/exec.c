#include <stdio.h>
#include <unistd.h>

int main(void)
{
  printf("Here I am, a lovely process minding my own business. I have something exciting to tell you...\n");

  char* prog = "echo";

  char* args[3];
  args[0] = prog;
  args[1] = "We seem to have changed to a new program";
  args[2] = NULL;
  execvp(prog, args); // will never return (except on error)

  printf("It would be horrible if I ouldn't tell you that the answer to everything in life is 42.\n");
}