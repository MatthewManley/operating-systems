#include <stdio.h>   /* printf, stderr, fprintf */
#include <unistd.h>  /* _exit, fork */
#include <iostream>
#include <sys/wait.h>

const int num_forks = 3;

int main(int argc, char* argv[]) {
    // Check that exactly 1 argument was passed in (excluding the first argument which is the name of the executed file)
    if (argc != 2){
        printf("Expected 1 argument, got %i\n", argc - 1);
        printf("Run this program with the following arguments:\n.%s filename\n", argv[0]);
        return 1;
    }

    // Forks "num_forks" number of child proccesses
    int PID = 0;
    
    PID = fork();

    // First child
    if (PID == 0){
        execl("/bin/ls", "ls", "-l", (char *)0);
        exit(EXIT_SUCCESS);
    }

    PID = fork();

    // Second child
    if (PID == 0) {
        execl("/bin/ps", "ps", "-ef", (char *)0);
        exit(EXIT_SUCCESS);
    }

    PID = fork();

    // Third child
    if (PID == 0) {
        execl("/bin/cat", "cat", "instructions.txt", (char *)0);
        exit(EXIT_SUCCESS);
    }

    // Wait for all three child processes to end
    int ret;
    wait(&ret);
    wait(&ret);
    wait(&ret);
    printf("main process terminates\n");
}