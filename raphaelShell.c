// Raphael Napinas
// CS 2600 Final
// Shell Program

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  raphaelShellLoop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

void raphaelShellLoop(void)
{
  char *line;
  char **arguments;
  int status;

  do {
    printf("> ");
    line = shellReadLine();
    arguments = shellSplitLine(line);

    free(line);
    free(arguments);
  } while(status);
}

#define SHELL_RL_BUFSIZE 1024

char *shellReadLine(void)
{
  int bufSize = SHELL_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufSize);
  int character;

  if (!buffer)
  {
    fprintf(stderr, "Raphael Shell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // Read character
    character = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (character == EOF || character == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }
    else
    {
      buffer[position] = character;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufSize)
    {
      bufSize += SHELL_RL_BUFSIZE;
      buffer = realloc(buffer, bufSize);
      if (!buffer)
      {
        fprintf(stderr, "Raphael Shell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  /* Using getline()
  char *line = NULL;
  ssize_t bufSize = 0; // have getline allocate a buffer for us

  if (getline(&line, &bufSize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We recieved an EOF
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
  */
}

#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"

char **shellSplitLine(char *line)
{
  int bufSize = SHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufSize * sizeof(char*));
  char *token;

  if (!tokens)
  {
    fprintf(stderr, "Raphael Shell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, SHELL_TOK_DELIM);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= bufSize)
    {
      bufSize += SHELL_TOK_BUFSIZE;
      tokens = realloc(tokens, bufSize * sizeof(char*));
      if (!tokens)
      {
        fprintf(stderr, "Raphael Shell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SHELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
