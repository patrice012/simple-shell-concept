#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Write a program that prints "$ ", 
 * wait for the user to enter a command, prints it on the next line.
 */

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        fflush(stdout);
        read = getline(&line, &len, stdin);
        if (read == -1) {
            break;
        }
        printf("%s", line);
    }

    free(line);
    return 0;
}
