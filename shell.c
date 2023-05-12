#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * split_arg - splite argument base on delimeter
 * @delim: current delimeter
 * @str: strings to split
 * @arr: array of delimeter strings
 * Return: 0
 */

void split_arg(char *str, char *delim, char **arr)
{
    int i = 0;
    char *temp = strtok(str, delim);
    while (temp != NULL)
    {
        arr[i++] = temp;
        /* get new token */
        temp = strtok(NULL, delim);
    }
    /* set the end t0 null */
    arr[i] = "\0";
}

/**
 * exec_program - execute a program
 * @path: path to the object file
 * @argv: process
 */

int exec_program(char *path,  char **argv)
{
    /*char *argv[] = {};;
    char *envp[] = { NULL };
    printf("line value3: %s\n", path);
    char **arr;
    split_arg(path, "/", arr);
    printf("%s \n", arr[0]);
    printf("%s \n", arr[1]);*/
    char *envp[] = { NULL };
    char *argv[] = {"bin/ls", "-l"};
    int i = execve(, argv, envp);
    if (i == -1)
    {
        dprintf(STDOUT_FILENO, "%s\n", "fail to run this program");
        exit(1);
    }
    return (i);
}


/**
 * exec - execute a program
 * @path: path to the object file
 */

int exec(char *path, int status)
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
        char *args[100];
        int i = 0;
        char *arg = strtok(path, " ");
        while (arg != NULL) {
            args[i++] = arg;
            arg = strtok(NULL, " ");
        }
        args[i] = NULL; //
        printf("line value2: %s\n", path);
        exec_program(args[0], args);
    }
    else
    {
        /* suspence parent process unti all child process finished*/
        wait(&status);
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
        printf("line value1: %s\n", path);
        exec(path, status);
    }

    free(path);
    return 0;
}
