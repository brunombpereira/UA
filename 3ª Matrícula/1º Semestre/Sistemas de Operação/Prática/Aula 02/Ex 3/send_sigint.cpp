#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Ensure the program receives a PID as an argument
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Convert the argument to a PID (process ID)
    pid_t pid = atoi(argv[1]);

    // Send the SIGINT signal to the process with the given PID
    if (kill(pid, SIGINT) == -1) {
        printf("Failed to send SIGINT");
        return EXIT_FAILURE;
    }

    printf("SIGINT signal sent to process with PID: %d\n", pid);

    return EXIT_SUCCESS;
}
