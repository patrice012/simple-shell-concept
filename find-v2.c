#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024
#define MAX_FILENAME_LEN 256

char *_get_cwd() {
    char *cwd = getcwd(buf, MAX_PATH_LEN);
    if (cwd == NULL) {
        free(buf);
        return NULL;
    }
    return cwd;
}

char* build_path(const char* dirname, const char* filename) {
    char* path = malloc(MAX_PATH_LEN);
    if (path == NULL) {
        return NULL;
    }
    snprintf(path, MAX_PATH_LEN, "%s/%s", dirname, filename);
    return path;
}

char* read_dir(const char* dirname, const char* filename) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return NULL;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcasecmp(entry->d_name, filename) == 0) {
            char* path = build_path(dirname, filename);
            closedir(dir);
            return path;
        }
    }
    closedir(dir);
    return NULL;
}

int which(const char* filename, char* result, size_t result_size) {
    char* path_env = getenv("PATH");
    if (path_env == NULL) {
        return -1;
    }
    char* path_copy = strdup(path_env);
    if (path_copy == NULL) {
        return -1;
    }
    char* dir = strtok(path_copy, ":");
    while (dir != NULL) {
        char* path = read_dir(dir, filename);
        if (path != NULL) {
            if (snprintf(result, result_size, "%s", path) >= (int)result_size) {
                free(path);
                free(path_copy);
                return -1;
            }
            free(path);
            free(path_copy);
            return 0;
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char* cwd = _get_cwd();
    if (cwd == NULL) {
        fprintf(stderr, "Failed to get current directory\n");
        return 1;
    }
    char result[MAX_PATH_LEN];
    int ret = which(argv[1], result, sizeof(result));
    if (ret != 0) {
        fprintf(stderr, "Failed to find %s\n", argv[1]);
        free(cwd);
        return 1;
    }
    printf("%s/%s\n", cwd, result);
    free(cwd);
    return 0;
}
