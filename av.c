#include <stdio.h>

/**
 * main - main function
 * @av: number of argument
 * @ac array of pointer
 * Return: int 0 for success
 */


/*Write a program that prints all the arguments, without using ac*/


int main(int ac, char **av)
{
    int i = 0;

    for (i = 0; i < ac; i++)
    {
        printf("%s\n", av[i]);
    }
}
