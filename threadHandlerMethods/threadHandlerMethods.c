#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "../constants/constants.h"
#include "../bufferHandlers/bufferHandlers.h"
#include "../dataProcessingMethods/dataProcessingMethods.h"
#include "../threadHandlerMethods/threadHandlerMethods.h"

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

void *handlePrintLimitedCharOutput(void *args)
{
  char *line;
  do
  {
    line = get_buff_3();
    printLimitedCharOutput(line);
  } while (!isTermFlag(line));

  return NULL;
}