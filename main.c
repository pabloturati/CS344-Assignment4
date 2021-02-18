#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "constants/constants.h"
#include "bufferHandlers/bufferHandlers.h"
#include "dataProcessingMethods/dataProcessingMethods.h"

#define STOP_SYMBOL "STOP\n"
#define TERM_SYMBOL "TERM"

int strEquals(char *str1, char *str2)
{
  return (strcmp(str1, str2) == 0);
}

int isTermFlag(char *line)
{
  return strEquals(line, TERM_SYMBOL);
}

void *handleReadLine(void *args)
{
  char *line = (char *)malloc(BUFFER_SIZE * sizeof(char));
  do
  {
    line = fgets(line, BUFFER_SIZE, stdin);
    //Place termination flag if end of file or STOP flag
    if (line == NULL || strcmp(line, STOP_SYMBOL) == 0)
      line = TERM_SYMBOL;
    put_buff_1(line);
  } while (!isTermFlag(line));
  return NULL;
}

void *replaceLineSeparatorBySpaceHandler(void *args)
{
  // printf("APP 1\n");
  char *line;
  do
  {
    line = get_buff_1();
    replaceLineSeparatorBySpace(line);
    put_buff_2(line);
  } while (!isTermFlag(line));
  return NULL;
}

void *handleReplacePlusSignPairs(void *args)
{
  char *line;
  do
  {
    line = get_buff_2();
    replacePlusSignPairs(line);
    put_buff_3(line);
  } while (!isTermFlag(line));
  return NULL;
}

void *handlePrintLimitedCharOutput()
{
  char *line;
  do
  {
    line = get_buff_3();
    printLimitedCharOutput(line);
  } while (!isTermFlag(line));

  return NULL;
}

int main(void)
{
  pthread_t readLineThreadId, replaceLineSeparatorBySpaceThreadId, replacePlusSignPairsThreadId, printToStdOutThreadId;

  // printf("HERE1\n");
  // Readline thread
  pthread_create(&readLineThreadId, NULL, handleReadLine, NULL);

  // Replace endline for spaces thread
  pthread_create(&replaceLineSeparatorBySpaceThreadId, NULL, replaceLineSeparatorBySpaceHandler, NULL);

  // // Replace '++' for '^' spaces thread
  pthread_create(&replacePlusSignPairsThreadId, NULL, handleReplacePlusSignPairs, NULL);

  // Print output to stdout therad
  pthread_create(&printToStdOutThreadId, NULL, handlePrintLimitedCharOutput, NULL);

  // printf("HERE2\n");
  pthread_join(readLineThreadId, NULL);
  pthread_join(replaceLineSeparatorBySpaceThreadId, NULL);
  pthread_join(replacePlusSignPairsThreadId, NULL);
  // printf("HERE-A\n");
  pthread_join(printToStdOutThreadId, NULL);

  // printf("HERE3\n");
  // Free memory that contains incomplete printouts
  if (rem != NULL)
    free(rem);

  // fprintf(stdout, "MY TEST\n");
  // printf("HERE4\n");
  return 0;
}
