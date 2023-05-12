#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * main - main function
 * Return: 0
 */


int main(void)
{
    /* create statut */
    int status, loop = 0;
    /* create a pid */
    pid_t child_pid;

    /* create a command object */
    char *argv[] =  {"/bin/ls", "-l", "/tmp", NULL};
    printf("Wait finish\n");

    while (loop < 5)
    {
        /* fork the current process */
        child_pid = fork();
        if (child_pid == -1)
        {
            dprintf(STDOUT_FILENO, "%s", "Error");
            return (1); /* indicate an error */
        }
        else if (child_pid == 0) /* execute the new process */
        {   
            /* execute the command */
            int i = execve(argv[0], argv, NULL);
            if (i == -1) /* execution fail */
            {
                dprintf(STDOUT_FILENO, "%s", "execution failed");
                exit(1);
            }
        }
        else
        {
            /* 
             * After forking, the parent process waits 
             * for each child to exit using the wait function.
             */
            wait(&status);
        }
        loop++;
    }
    printf("Wait finish\n");
    
}
