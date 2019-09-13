#include <stdio.h>   /* printf, stderr, fprintf */
#include <unistd.h>  /* _exit, fork */
#include <iostream>

const int num_forks = 3;

int main(int argc, char* argv[]) {
    // Check that exactly 1 argument was passed in (excluding the first argument which is the name of the executed file)
    if (argc != 2){
        printf("Expected 1 argument, got %i\n", argc - 1);
        printf("Run this program with the following arguments:\n.%s integer\n", argv[0]);
        return 1;
    }

    // Store the argument in its own variable so that we don't have to keep referencing it via argv[1]
    char* argument = argv[1];

    // Try to convert it to an int
    int n;
    try
    {
        n = std::stoi(argument);
    }
    catch(std::invalid_argument const &e)
    {
        printf("Argument \"%s\" is not a number!\n", argument);
        printf("Run this program with the following arguments:\n.%s integer\n", argv[0]);
        return 1;
    }

    // Forks "num_forks" number of child proccesses
    int PID = 1;
    for (int i = 0; i < num_forks; i++) //creates 3 children process
    {
        PID = fork();

        // If PID equals 0, it is a child process and should not create grandchildren, therefore break out of the loop
        if (PID == 0){
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {   
        // If PID equals 0 then it is a child process
        if (PID == 0) {
            printf("This is a child process, my PID is %i\n", getpid());
        } else {
            printf("This is the main process, my PID is %i\n", getpid());
        }
        sleep(2);
    }
    
    return 0;
}