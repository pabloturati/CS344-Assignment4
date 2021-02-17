#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
// #include "constants/constants.h"
#define BUFFER_SIZE 1000
#define PRINT_SIZE 80
#define MAX_LINES 48

//Initialize mutex and conditional variable
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t bufferHasContent = PTHREAD_COND_INITIALIZER;

char lines[MAX_LINES][BUFFER_SIZE];

static int strCount = 0;
static int replaceLineBreakCount = 0;
static int replaceSignsCount = 0;
static int printCount = 0;
static int printPos = 0;

void *handleReadLine(void *args)
{
  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
  // pthread_mutex_lock(&mutex);
  while (fgets(buffer, BUFFER_SIZE, stdin) && strcmp(buffer, "STOP\n") != 0)
  {
    strcpy(lines[strCount], buffer);
    strCount += 1;
  }
  // pthread_mutex_unlock(&mutex);
  free(buffer);
  return NULL;
}

void replaceLineSeparatorBySpace()
{
  char *pos = strchr(lines[replaceLineBreakCount], '\n');
  *pos = ' ';
}

void *replaceLineSeparatorBySpaceHandler()
{
  while (replaceLineBreakCount < strCount)
  {
    replaceLineSeparatorBySpace();
    ++replaceLineBreakCount;
  }
  return NULL;
}

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

void replacePlusSignPairs()
{

  char *pos = strstr(lines[replaceSignsCount], "++");
  while (pos != NULL)
  {
    *pos = '^';
    shiftString(pos);
    pos = strstr(lines[replaceSignsCount], "++");
  }
}

void *handleReplacePlusSignPairs(void *args)
{
  while (replaceSignsCount < replaceLineBreakCount)
  {
    replacePlusSignPairs();
    ++replaceSignsCount;
  }
  return NULL;
}

void printLimitedCharOutput()
{
  char *line = lines[printCount];
  int lineLength = strlen(line);

  int currIdx = 0;
  while (currIdx < lineLength)
  {
    printf("%c", line[currIdx]);
    ++currIdx;
    ++printPos;
    if (printPos % PRINT_SIZE == 0)
    {
      printf("\n");
    }
  }
}

void *handlePrintLimitedCharOutput()
{

  // pthread_mutex_lock(&mutex);
  // while (strCount == 0)
  // pthread_cond_wait(&bufferHasContent, &mutex);

  while (printCount < strCount)
  {
    printLimitedCharOutput();
    ++printCount;
  }

  // pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void)
{
  pthread_t readLineThreadId, replaceLineSeparatorBySpaceThreadId, replacePlusSignPairsThreadId, printToStdOutThreadId;

  // Readline thread
  pthread_create(&readLineThreadId, NULL, handleReadLine, NULL);

  // Replace endline for spaces thread
  pthread_create(&replaceLineSeparatorBySpaceThreadId, NULL, replaceLineSeparatorBySpaceHandler, NULL);
  pthread_join(replaceLineSeparatorBySpaceThreadId, NULL);

  // Replace '++' for '^' spaces thread
  pthread_create(&replacePlusSignPairsThreadId, NULL, handleReplacePlusSignPairs, NULL);
  pthread_join(replacePlusSignPairsThreadId, NULL);

  // Print output to stdout therad
  pthread_create(&printToStdOutThreadId, NULL, handlePrintLimitedCharOutput, NULL);
  pthread_join(printToStdOutThreadId, NULL);

  // printf("HERE\n");
  // for (int i = 0; i < strCount; i++)
  // {
  //   printf("Line %d:  %s", i, lines[i]);
  // }

  return 0;
}
