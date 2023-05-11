#include <stdio.h>
#include <unistd.h>

/**
 * main - main function
 * Return: 0 for success
 */

/*Write a program that prints the PID of the parent process*/

int main(void)
{
    pid_t ppid, pid;

    ppid = getppid();
    pid = getpid();
    printf("The parent pid %d\n", ppid);
    printf("The current pid %d\n", pid);
    return 0;
}
