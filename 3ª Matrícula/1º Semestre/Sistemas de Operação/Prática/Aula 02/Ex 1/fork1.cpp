#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(void)
{
  printf("Before the fork: PID = %d, PPID = %d\n", getpid(), getppid());

  int ret = pfork(); // equivalent to fork(), dealing internally with error situations
  
  if (ret != 0)
  {
    printf("Father:\nAfter the fork: PID = %d, PPID = %d\n",getpid(), getppid());
    bwRandomDelay(1000, 100000); // added to enhance the occurrence of different outputs
    printf("  Was I printed by the parent or by the child process? I was printed by the father.\n");
  } else
  {
    printf("Child:\nAfter the fork: PID = %d, PPID = %d\n",getpid(), getppid());
    bwRandomDelay(1000, 100000); // added to enhance the occurrence of different outputs
    printf("  Was I printed by the parent or by the child process? I was printed by the child.\n");
  }
  
  return EXIT_SUCCESS;
}

