#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/**
  * _getline - read data to stdin 
  * @lineptr: output data type
  * @n: number of bytes to read
  * @stream: data provider
  */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t nread = 0;
  char c;
  int i = 0, max_size = 1024;

  // Allocate memory for line
  buffer = (char *)malloc(sizeof(char) * bufsize);
  if (!buffer) {
      perror("malloc");
      exit(EXIT_FAILURE);
  }

  /* Read input from user */

  while (1)
  {
    /* get each character */
    c = getchar();
    /* if char is end of line or EOF */
    if (c == EOF || c == '\n')
      /* append end of string */
      {
        buffer[i] = '\0';
        break;
      }
    else
      buffer[i] = c;
    i++;
    nread++;

    /* 
     * check if buffer is empty
     * if true increase the size else continue 
     */
    if (i == bufsize)
    {
      bufsize += max_size;
      /* reallocate memory */
      buffer = (char *)realloc(buffer, sizeof(char) * max_size);
      if (!buffer)
      {
        perror("realloc");
        exit(EXIT_FAILURE);
      }
    }
  }
  *lineptr = buffer;
  

  /* if user enter end of file free buffer and return NULL */
  if (i == 0 && buffer[i] == '\0')
  {
    /*free(buffer);*/
    return (0);
  }
  return (nread);
}



int main() {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while (1) {
      printf("$ ");
      fflush(stdout);
      read = _getline(&line, &len, stdin);
      if (read == -1) {
          break;
      }
      printf("%s\n", line);
  }

  free(line);
  return 0;
}
