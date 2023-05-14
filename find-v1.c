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

/**
 * build_path - build the absolute path for the given file 
 * base on the current directory
 * @full_path: path to build
 * @cwd: current working directory path
 * @filename: filename to search
 * @size: size of the filename argument
 * Return: 0 if found and -1 else
 */

int build_path(char *full_path, char *cwd, char *filename, size_t size)
{
    snprintf(full_path, size, "%s/%s", cwd, filename);

    struct stat st;
    if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)) {
        return (0);
    }
    return (-1);
}



/**
 * read_dir - read all content of the given path 
 * and compare each files to the provider file 
 * @path: path to look for files
 * Return: 0 if found and -1 else
 */

int read_dir(char *path, char *filename) {
    DIR *dir;
    struct dirent *ent;
    int exist = -1;

    if ((dir = opendir(path)) != NULL) {
        // print all the files and directories within directory
        while ((ent = readdir(dir)) != NULL) {
            /*printf("the name: %s\n", ent->d_name);*/
            exist = strcmp(ent->d_name, filename);
            if (exist == 0)
                break;
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
    return ((exist == 0) ? 0 : -1);
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
    char *path = strtok(path_env, ":");
    struct stat st;
    int found = 0, exist;

    while (path != NULL && !found)
    {
        puts(path);
        /* read all files and compare each file */
        exist = read_dir(path, filename);
        /* if the file don't exist in this dirs go to the next dirs */
        if (exist != 0)
        {
            path = strtok(NULL, ":");
            continue;
        }
        else if (exist == 0)
        {
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
            printf("_which f_path: %s\n", full_path);

            if (stat(full_path, &st))
            {
                strncpy(result, full_path, result_size);
                found = 1;
            }  
        }
        path = strtok(NULL, ":");
    }

    return found ? 0 : -1;
}



int main(int argc, char *argv[]) {
    
    char full_path[MAX_SIZE];
    char f_path[MAX_SIZE];
    size_t size = sizeof(full_path) / sizeof(full_path[0]);
    printf("value: %ld\n", size + '0');
    int found, i = 1;

   while (argv[i] != NULL)
   {    
        char *filename = argv[i];
        char *cwd = _get_cwd(full_path, MAX_SIZE);
        /* search in current directory */
        found = build_path(full_path, cwd, filename, size);
        /* if found in the current directory */
        if (found == 0)
        {
            printf("%s FOUND\n", full_path);
        }
        else
        {
            /* else search in PATH */
            int ret = _which(filename, f_path, size);
            printf("f_path: %s\n", f_path);
            if (ret == 0)
            {
                printf("%s FOUND\n", f_path);
                return (0);
            }
            else
            {
                fprintf(stderr, "%s: command not found\n", argv[1]);
                return (-1);
            }
        }
        i++;
   }
    return (0);
}
