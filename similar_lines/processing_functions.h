#ifndef PROCESSING_FUNCTIONS
#define PROCESSING_FUNCTIONS

#include "structures.h"

extern void sortNumbers(List_t *wsk);
extern char* increaseNotnumTab(char *wyraz, int *rozmiar, char znak, int *pot_rozmiar);
extern void insertNan(char *wyraz, int rozmiar, List_t *wsk);
extern void sortNotnumbers(List_t *wsk);
extern void increaseNumTab(struct List_t *wsk);
extern bool mightHex(List_t *wsk, int indic);
extern void processData(List_t *wsk);

#endif