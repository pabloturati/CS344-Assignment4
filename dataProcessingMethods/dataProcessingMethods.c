#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "../constants/constants.h"

// Replace data by space helper methods

void replaceLineSeparatorBySpace(char *line)
{
  char *pos = strchr(line, '\n');
  *pos = ' ';
}

// Replace ++ by ^ helper methods

void shiftString(char *pos)
{
  char *next = pos + sizeof(char);
  char *secondNext = next + sizeof(char);
  while (*next != '\0')
  {
    *next = *secondNext;
    next = next + sizeof(char);
    secondNext = next + sizeof(char);
  }
}

void replacePlusSignPairs(char *line)
{

  char *pos = strstr(line, "++");
  while (pos != NULL)
  {
    *pos = '^';
    shiftString(pos);
    pos = strstr(line, "++");
  }
}

void printLimitedCharOutput(char *line)
{
  int BUF_SIZE = BUFFER_SIZE + PRINT_SIZE;
  char mergedLine[BUF_SIZE];
  if (rem != NULL)
  {
    // Merge previous remainder to line
    snprintf(mergedLine, BUF_SIZE, "%s%s", rem, line);
    free(rem);
  }
  else
  {
    snprintf(mergedLine, BUF_SIZE, "%s", line);
  }

  int lineLength = strlen(mergedLine);
  int heigth = lineLength / PRINT_SIZE;
  char *tempBuff = calloc(PRINT_SIZE + 1, sizeof(char));

  int currIdx = 0;

  int i = 0;
  for (i = 0; i < heigth; i++)
  {
    strncpy(tempBuff, mergedLine + currIdx + (i * PRINT_SIZE), PRINT_SIZE);
    fprintf(stdout, "%s\n", tempBuff);
  }
  // If has a remainder, save it
  if (lineLength % PRINT_SIZE > 0)
  {
    rem = calloc(PRINT_SIZE, sizeof(char));
    char *incomStr = &mergedLine[i * PRINT_SIZE];
    strcpy(rem, incomStr);
  }
  free(tempBuff);
}