#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char *command = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Read the command entered by the user
        read = getline(&command, &len, stdin);
        if (read == -1) {
            break;
        }

        // Remove the newline character from the end of the command
        command[read - 1] = '\0';

        // Create a child process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *argv[] = {command, NULL};
            if (execvp(command, argv) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            if (wait(&status) == -1) {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    free(command);
    return 0;
}
