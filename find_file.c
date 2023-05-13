#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_SIZE 1024

int _which(char *filename, char *result, size_t result_size);


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


int build_path(char *full_path, char *cwd, char *filename, size_t size)
{
    snprintf(full_path, size, "%s/%s", cwd, filename);

    struct stat st;
    if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)) {
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}

int read_dir(char *path) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) != NULL) {
        // print all the files and directories within directory
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return EXIT_FAILURE;
    }
    return 0;
}


/**
 * which - search for a file in the PATH environment variable
 * @filename: the name of the file to search for
 * @result: a buffer to store the full path of the file if found
 * @result_size: the size of the buffer
 *
 * Return: 0 if the file was found, -1 otherwise
 */
int _which(char *filename, char *result, size_t result_size)
{
    char *path_env = getenv("PATH");
    puts(path_env);
    char *path = strtok(path_env, ":");
    struct stat st;
    int found = 0;

    while (path != NULL && !found)
    {

        /* check if the file is in the this directory */
        /* open all directori and compare all files with our file name
         * if mach the go and do all staff below else call strtok again and redo the same process*/
        size_t path_len = strlen(path);
        size_t filename_len = strlen(filename);
        size_t full_path_len = path_len + 1 + filename_len;

        char *full_path = malloc(full_path_len + 1);
        if (full_path == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        snprintf(full_path, full_path_len + 1, "%s/%s", path, filename);

        if (stat(full_path, &st))
        {
            strncpy(result, full_path, result_size);
            found = 1;
        }

        free(full_path);
        path = strtok(NULL, ":");
    }

    return found ? 0 : -1;
}



int main(int argc, char *argv[]) {
    
    char full_path[MAX_SIZE];
    size_t size = sizeof(full_path) / sizeof(full_path[0]);
    int found, i = 1;

   while (argv[i] != NULL)
   {    
        char *filename = argv[i];
        char *cwd = _get_cwd(full_path, MAX_SIZE);
        found = build_path(full_path, cwd, filename, size);
        /* if found in current directory */
        if (!found)
            printf("%s FOUND\n", full_path);
        else
        {
            /* else search in PATH */
            int ret = _which(filename, full_path, size);
            if (ret == 0)
            {
                printf("%s FOUND\n", full_path);
                return EXIT_SUCCESS;
            }
            else
            {
                fprintf(stderr, "%s: command not found\n", argv[1]);
                return (EXIT_FAILURE);
            }
        }
        i++;
   }
    return (EXIT_SUCCESS);
}
