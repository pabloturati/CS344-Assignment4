#ifndef CONSTANTS_H
#define CONSTANTS_H
// #include <pthread.h>
#define BUFFER_SIZE 1000
#define PRINT_SIZE 80
#define MAX_LINES 48
#define STOP_SYMBOL "STOP\n"
#define TERM_SYMBOL "TERM"

// Print to stdout helper methods
char *rem;

extern char buffer_1[MAX_LINES][BUFFER_SIZE];
int count_1;
int prod_idx_1;
int con_idx_1;
pthread_mutex_t mutex_1;
pthread_cond_t full_1;

extern char buffer_2[MAX_LINES][BUFFER_SIZE];
int count_2;
int prod_idx_2;
int con_idx_2;
pthread_mutex_t mutex_2;
pthread_cond_t full_2;

extern char buffer_3[MAX_LINES][BUFFER_SIZE];
int count_3;
int prod_idx_3;
int con_idx_3;
pthread_mutex_t mutex_3;
pthread_cond_t full_3;

int strEquals(char *, char *);
int isTermFlag(char *);

#endif