#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * _strtok - use srtok function
 * @str: string to split
 * @delim: delimiter to use
 * Return: char
 */

char *_strtok(char *str, const char *delim)
{
    return (strtok(str, delim));
}

/*
 * Write a program that prints "$ ", 
 * wait for the user to enter a command, prints it on the next line.
 */

int main() {
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;
    char *str, *delim = " ";

    while (1) {
        printf("$ ");
        fflush(stdout);
        read = getline(&buffer, &len, stdin);
        if (read == -1) {
            break;
        }

        /* first call */
        str = _strtok(buffer, delim);
        while (str)
        {
            /* 
             * with a NULL pointer as the first argument to continue 
             * tokenizing the input string from where we left off.
             */
            printf("%s\n", str);
            str = _strtok(NULL, delim);
        }
    }

    free(buffer);
    return 0;
}
