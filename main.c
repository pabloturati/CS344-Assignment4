#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "constants/constants.h"
#include "bufferHandlers/bufferHandlers.h"
#include "dataProcessingMethods/dataProcessingMethods.h"

void *handleReadLine(void *args)
{
  char *line = (char *)malloc(BUFFER_SIZE * sizeof(char));
  while (fgets(line, BUFFER_SIZE, stdin) && strcmp(line, "STOP\n") != 0)
  {
    put_buff_1(line);
  }
  free(line);
  return NULL;
}

void *replaceLineSeparatorBySpaceHandler(void *args)
{
  char *line;
  do
  {
    line = get_buff_1();
    replaceLineSeparatorBySpace(line);
    put_buff_2(line);
  } while (line != NULL);
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
  } while (line != NULL);
  return NULL;
}

void *handlePrintLimitedCharOutput()
{
  char *line;
  do
  {
    line = get_buff_3();
    printLimitedCharOutput(line);
  } while (line != NULL);

  return NULL;
}

int main(void)
{
  pthread_t readLineThreadId, replaceLineSeparatorBySpaceThreadId, replacePlusSignPairsThreadId, printToStdOutThreadId;

  // Readline thread
  pthread_create(&readLineThreadId, NULL, handleReadLine, NULL);

  // Replace endline for spaces thread
  pthread_create(&replaceLineSeparatorBySpaceThreadId, NULL, replaceLineSeparatorBySpaceHandler, NULL);

  // // Replace '++' for '^' spaces thread
  pthread_create(&replacePlusSignPairsThreadId, NULL, handleReplacePlusSignPairs, NULL);

  // Print output to stdout therad
  pthread_create(&printToStdOutThreadId, NULL, handlePrintLimitedCharOutput, NULL);

  pthread_join(readLineThreadId, NULL);
  pthread_join(replaceLineSeparatorBySpaceThreadId, NULL);
  pthread_join(replacePlusSignPairsThreadId, NULL);
  pthread_join(printToStdOutThreadId, NULL);

  // Free memory that contains incomplete printouts
  if (rem != NULL)
    free(rem);
  return 0;
}
