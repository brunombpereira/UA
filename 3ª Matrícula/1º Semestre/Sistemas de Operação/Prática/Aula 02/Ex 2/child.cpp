#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(int argc, char *argv[])
{
    execlp("ls", "ls", "-l", NULL);

   return EXIT_SUCCESS;
}
