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
