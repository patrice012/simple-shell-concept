#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_SIZE 1024

int _which(char *filename, char *result, size_t result_size);
// int which(char *filename, char *result, char *dir);


int main(int ac, char *av[])
{
    if (ac < 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s", "_which filename ...");
        exit (EXIT_FAILURE);
    }
    int found;
    /* create temporary buffer */
    char buffer[MAX_SIZE];

    /* call _which function with argument */
    int resp = _which(av[1], buffer, MAX_SIZE);
    if (resp == 0)
    {
        printf("%s FOUND\n", buffer);
        return (EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "%s: command not found\n", av[1]);
        return (EXIT_FAILURE);
    }
}


/**
 * _which - search for file or directory
 * @av: array contains files or drectories to find
 * @st: stat object
 */

int _which(char *filename, char *result, size_t result_size)
{
    /* get env path */
    char *path_env = getenv("PATH");
    /* split path */
    char *path = strtok(path_env, ":");
    struct stat st;
    int found = 0;

    while (path != NULL && !found)
    {
        /*  get amount of size required */
        size_t path_len = strlen(path);
        size_t filename_len = strlen(filename);
        size_t full_path_len = path_len + filename_len + 1;

        /* allocate bytes */
        char *full_path = (char *)malloc(sizeof(char) * full_path_len);
        if (full_path == NULL)
        {
            dprintf(STDERR_FILENO, "%s", "malloc failed");
            exit(EXIT_FAILURE);
        }
        /* create the full path*/
        snprintf(full_path, full_path_len + 1, "%s/%s", path, filename);
        /* check if file exist */
        int exist = stat(full_path, &st);
        /* if file exist and is a regular file */
        if (exist == 0)
        {
            /* copy the full_path into result */
            strncpy(result, full_path, result_size);
            found = 1;
        }

        /*free(full_path);*/
        path = strtok(NULL, ":");

    }
    return (0);
}


int which(char *filename, char *result, char *dir)
{
    char full_path[MAX_SIZE];
    struct stat st;
    int found = 0;

    // Check if the specified directory exists
    if (dir != NULL && stat(dir, &st) == -1)
    {
        return -1;
    }

    // Search the specified directory or the default PATH directories
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        return -1;
    }

    char *path = strtok(path_env, ":");
    while (path != NULL && !found)
    {
        // Construct the full path to the file
        if (dir == NULL)
        {
            snprintf(full_path, MAX_SIZE, "%s/%s", path, filename);
        }
        else
        {
            snprintf(full_path, MAX_SIZE, "%s/%s/%s", path, dir, filename);
        }

        // Check if the file exists and is a regular file
        if (stat(full_path, &st) == 0)
        {
            strncpy(result, full_path, MAX_SIZE);
            found = 1;
        }

        path = strtok(NULL, ":");
    }

    return found ? 0 : -1;
}

