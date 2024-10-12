#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(void)
{
  printf("Before the fork: PID = %d, PPID = %d\n", getpid(), getppid());

  pid_t ret = pfork();
  if (ret == 0)
  {
    for (int i = 1; i < 11; i++)
    {
      printf("%d ",i);
    }
  }
  else
  {
    pwait(NULL);

    for (int i = 11; i < 21; i++) {
      printf("%d ",i);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}

