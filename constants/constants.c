#include <pthread.h>
#include <string.h>
#include "constants.h"

/*****   Mutual exclusion and conditional variables  ****/
/* Reference: Code adapted in parts from CS344 class example: 6_5_prod_cons_pipeline.c-2  https://repl.it/@cs344/65prodconspipelinec */

// Buffer 1.  Shared between 'get input' and 'replace line separators' threads
char buffer_1[MAX_LINES][BUFFER_SIZE];
// Number of items in the buffer
int count_1 = 0;
// Index where the input thread will put the next item
int prod_idx_1 = 0;
// Index where the square-root thread will pick up the next item
int con_idx_1 = 0;
// Initialize the mutex for buffer 1
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 1
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;

// Buffer 2.  Shared between 'replace line separators' and 'replace + sign' threads
char buffer_2[MAX_LINES][BUFFER_SIZE];
// Number of items in the buffer
int count_2 = 0;
// Index where the input thread will put the next item
int prod_idx_2 = 0;
// Index where the square-root thread will pick up the next item
int con_idx_2 = 0;
// Initialize the mutex for buffer 2
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 2
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;

// Buffer 3.  Shared between 'replace + sign' and 'print line' threads
char buffer_3[MAX_LINES][BUFFER_SIZE];
// Number of items in the buffer
int count_3 = 0;
// Index where the input thread will put the next item
int prod_idx_3 = 0;
// Index where the square-root thread will pick up the next item
int con_idx_3 = 0;
// Initialize the mutex for buffer 3
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
// Initialize the condition variable for buffer 3
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;

/*****   String comparison methods  ****/

// Compares two strings.  Returns 1 (TRUE) if strings are identical, else 0 (FALSE).
int strEquals(char *str1, char *str2)
{
  return (strcmp(str1, str2) == 0);
}

// Compares a string to the TERM_SYMBOL constant.  Returns 1 (TRUE) if strings is identical to the TERM_SYMBOL, else 0 (FALSE).
int isTermFlag(char *line)
{
  return strEquals(line, TERM_SYMBOL);
}