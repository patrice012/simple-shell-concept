#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
    int i;
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    printf("Before execve\n");
    i = execve(argv[0], argv, NULL);
    if (i == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
    return (0);
}
