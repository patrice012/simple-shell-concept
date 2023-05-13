#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * exec_program - execute a program
 * @path: path to the object file
 * @argv: process
 */

int exec_program(char *path)
{
    char *envp[] = { NULL };
    char *argv[] = {path, NULL};
    int i = execve(path, argv, envp); // change argv to args
    if (i == -1)
    {
        dprintf(STDERR_FILENO, "%s\n", "fail to run this program");
        exit(1);
    }
    return (i);
}


/**
 * exec - execute a program
 * @path: path to the object file
 */

int exec(char **exec_path, int *status)
{
    /* create pid */
    pid_t child_pid;
    /* fork new process */
    child_pid = fork();
    if (child_pid == -1)
    {
        dprintf(STDOUT_FILENO, "%s\n", "can't create new process");
    }
    else if (child_pid == 0)
    {
        exec_program(*exec_path);
    }
    else
    {
        /* suspence parent process unti all child process finished*/
        wait(status);
    }
}

/*
 * Write a program that prints "$ ", 
 * wait for the user to enter a command, prints it on the next line.
 */

int main() {
    char *path = NULL;
    size_t len = 0;
    ssize_t read;
    int status;

    while (1) {
        printf("$ ");
        fflush(stdout);
        read = getline(&path, &len, stdin);
        if (read == -1) {
            break;
        }
        path[read - 1] = '\0';
        exec(&path, &status);
    }

    free(path);
    return 0;
}
