#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "../constants/constants.h"

int PRINT_BUFFER_SIZE = BUFFER_SIZE + PRINT_SIZE;

/****** Replace line break helper methods *******/

// Replaces line breaks (if any) for space characters
void replaceLineSeparatorBySpace(char *line)
{
  char *pos = strchr(line, LINE_BREAK_CHATACTER);
  if (pos != NULL)
    *pos = SPACE_CHARACTER;
}

/****** Replace "++" symbol pair helper methods *******/

// Shift and string (array) one position left from the position give by the pos pointer
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

// Finds every ++ sign pair, changes it for the ^ symbol.
void replacePlusSignPairs(char *line)
{

  char *pos = strstr(line, PLUS_PLUS_SYMBOL);
  while (pos != NULL)
  {
    *pos = UP_ARROY_CHARACTER;
    shiftString(pos);
    pos = strstr(line, PLUS_PLUS_SYMBOL);
  }
}

/****** Print to standard out helper methods *******/

// Merges incomplete lefover print from previous run (if any)
void mergeIncompletePrint(char mergedLine[], char *line)
{
  // Chefks if there is a remainder from previous print, concatenate it.
  if (rem != NULL)
  {
    // Merge previous remainder to line
    snprintf(mergedLine, PRINT_BUFFER_SIZE, "%s%s", rem, line);
    free(rem);
  }
  else
    snprintf(mergedLine, PRINT_BUFFER_SIZE, "%s", line);
}

// Saves incomplete lefover print from previous run to be used in next thread call.
void saveIncompletePrintout(int lineLength, char *mergedLine, int pos)
{
  // Checks if there is a remainder from the last print out and, if so, save it
  if (lineLength % PRINT_SIZE > 0)
  {
    rem = calloc(PRINT_SIZE, sizeof(char));
    char *incomStr = &mergedLine[pos * PRINT_SIZE];
    strcpy(rem, incomStr);
  }
}

// Handles the print operation of each line to standard out
void printLimitedCharOutput(char *line)
{
  // Allocate memory to concatename previous printout remainder with new line
  char mergedLine[PRINT_BUFFER_SIZE];
  mergeIncompletePrint(mergedLine, line);

  // Calculate total print length
  int lineLength = strlen(mergedLine);

  // Calculate full 80 char lines
  int heigth = lineLength / PRINT_SIZE;

  // Temporary print buffer to store the 80 characters to be printed
  char *tempBuff = calloc(PRINT_SIZE + 1, sizeof(char));

  // Index of the intire print
  int currIdx = 0;

  // Line height index
  int i = 0;
  for (i = 0; i < heigth; i++)
  {
    // Save the 80 characters to temporary mememory location
    strncpy(tempBuff, mergedLine + currIdx + (i * PRINT_SIZE), PRINT_SIZE);
    // Print to std out the 80 characters
    fprintf(stdout, "%s\n", tempBuff);
  }
  saveIncompletePrintout(lineLength, mergedLine, i);
  free(tempBuff);
}