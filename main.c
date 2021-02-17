#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
// #include "constants/constants.h"
#define BUFFER_SIZE 1001
#define PRINT_SIZE 80

//Initialize mutex and conditional variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufferHasContent = PTHREAD_COND_INITIALIZER;

static int strCount = 0;

void *readLine(void *buffer)
{
  pthread_mutex_lock(&mutex);
  fgets(buffer, BUFFER_SIZE, stdin);
  strCount += 1;
  pthread_cond_signal(&bufferHasContent);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *replaceLineSeparatorBySpace(void *buffer)
{
  char *pos = strchr(buffer, '\n');
  *pos = ' ';
  return NULL;
}

void shiftString(char *buffer, char *pos)
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

void *replacePlusSignPairs(void *buffer)
{

  char *pos = strstr(buffer, "++");
  while (pos != NULL)
  {
    *pos = '^';
    shiftString(buffer, pos);
    pos = strstr(buffer, "++");
  }
  return NULL;
}

void printLimitedCharOutput(void *buffer)
{
  int counter = 0;
  int endIdx = PRINT_SIZE;
  char *printBuff = (char *)calloc(PRINT_SIZE, sizeof(char));
  int buffLength = strlen(buffer);
  char *start;
  while (endIdx <= buffLength)
  {
    start = &buffer[counter];
    strncpy(printBuff, start, endIdx - counter);
    fprintf(stdout, "%s\n", printBuff);
    counter = endIdx;
    endIdx += PRINT_SIZE;
  }
  if (endIdx <= buffLength + PRINT_SIZE)
  {
    start = &buffer[counter];
    strncpy(printBuff, start, endIdx - counter);
    fprintf(stdout, "%s", printBuff);
    counter = endIdx;
    endIdx += PRINT_SIZE;
  }
  free(printBuff);
  strCount -= 1;
}

void *handlePrintLimitedCharOutput(void *buffer)
{

  pthread_mutex_lock(&mutex);
  while (strCount == 0)
    pthread_cond_wait(&bufferHasContent, &mutex);
  printLimitedCharOutput(buffer);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void)
{
  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
  pthread_t readLineThreadId, replaceLineSeparatorBySpaceThreadId, replacePlusSignPairsThreadId, printToStdOutThreadId;

  // Readline thread
  pthread_create(&readLineThreadId, NULL, readLine, buffer);
  // // Replace endline for spaces thread
  // pthread_create(&replaceLineSeparatorBySpaceThreadId, NULL, replaceLineSeparatorBySpace, buffer);
  // // Replace '++' for '^' spaces thread
  // pthread_create(&replacePlusSignPairsThreadId, NULL, replacePlusSignPairs, buffer);
  // Print output to stdout therad
  pthread_create(&printToStdOutThreadId, NULL, handlePrintLimitedCharOutput, buffer);

  pthread_join(readLineThreadId, NULL);
  // pthread_join(replaceLineSeparatorBySpaceThreadId, NULL);
  // pthread_join(replacePlusSignPairsThreadId, NULL);
  pthread_join(printToStdOutThreadId, NULL);

  free(buffer);
  return 0;
}
