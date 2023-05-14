#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_SIZE 1024

char *_which(char *filename);

/**
 * _get_cwd - get the current working directory
 * @buffer: temporary location
 * @size: size of the buffer
 * Return: pointer to string
 */
char *_get_cwd(__attribute__((unused)) char *buf, size_t size __attribute__((unused)))
{
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
    return (cwd);
}

int main(int argc, char *argv[]) {
    
    char full_path[MAX_SIZE];
    size_t size = sizeof(full_path) / sizeof(full_path[0]);
    int found, i = 1;

    while (argv[i] != NULL)
    {    
        char *filename = argv[i];
        char *cwd = _get_cwd(full_path, MAX_SIZE);
        /* create absolute path */
        snprintf(full_path, size, "%s/%s", cwd, filename);
        struct stat st;
        /* look for file in current directory */
        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)) {
            printf("%s FOUND\n", full_path);
        } else {
            /* else search in PATH */
            char *path = _which(filename);
            if (path != NULL) {
                printf("%s FOUND\n", path);
            } else {
                fprintf(stderr, "%s: command not found\n", argv[1]);
                return (EXIT_FAILURE);
            }
        }
        i++;
   }
    return (EXIT_SUCCESS);
}

/**
 * which - search for a file in the PATH environment variable
 * @filename: the name of the file to search for
 *
 * Return: the full path of the file if found, or NULL otherwise
 */
char *_which(char *filename) {
    char *path_env = getenv("PATH");
    char *path = strtok(path_env, ":");
    struct stat st;

    while (path != NULL)
    {
        char full_path[MAX_SIZE];
        /* create absolute path */
        snprintf(full_path, MAX_SIZE, "%s/%s", path, filename);
        /* look for file in this particular dir */
        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)) {
            char *result = malloc(MAX_SIZE);
            strncpy(result, full_path, MAX_SIZE);
            return (result);
        }
        path = strtok(NULL, ":");
    }

    return NULL;
}
