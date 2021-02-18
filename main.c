#include <stdlib.h>
#include <pthread.h>
#include "constants/constants.h"
#include "bufferHandlers/bufferHandlers.h"
#include "dataProcessingMethods/dataProcessingMethods.h"
#include "threadHandlerMethods/threadHandlerMethods.h"

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
