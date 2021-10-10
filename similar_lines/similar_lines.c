#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "structures.h"
#include "check.h"
#include "load.h"
#include "processing_functions.h"
#include "print.h"

int main(void) {
    List_t *head = NULL;
    List_t *ptr = NULL;

    getLines(&head, &ptr);

    ptr->next = NULL;

    processData(head);
    List_t *wsk = head;

    printResult(wsk, &head);

    return(0);
}


