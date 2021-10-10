#ifndef PRINT
#define PRINT
#include "structures.h"

extern bool compareNumbers(List_t *first_item, List_t *second_item);
extern bool compareNotnumbers(List_t *first_item, List_t *second_item);
extern List_t* deleteNode(List_t *wsk);
extern void deleteFirst(List_t **head);
extern void printResult(List_t *wsk, List_t **head);

#endif