#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structures.h"

bool compareNumbers(List_t *first_item, List_t *second_item) {
    if(first_item->quantity_numbers != second_item->quantity_numbers)
        return false;

    for(int i=0; i<first_item->quantity_numbers; i++) {
        if(first_item->numbers[i] != second_item->numbers[i]) {
            return false;
        }
    }
    return true;
}

bool compareNotnumber_ts(List_t *first_item, List_t *second_item) {
    if(first_item->quantity_notnumbers != second_item->quantity_notnumbers)
        return false;

    for(int i=0; i<first_item->quantity_notnumbers; i++) {
        if(first_item->notnumbers[i].notnumber_size != 
        second_item->notnumbers[i].notnumber_size)
            return false;

        for(int j=0; j<first_item->notnumbers[i].notnumber_size; j++) {
            if(first_item->notnumbers[i].characters[j] != 
            second_item->notnumbers[i].characters[j])
                return false;
        }

    }
    return true;
}

List_t* deleteNode(List_t *wsk) {
    List_t *pat = wsk->next;

    free(wsk->numbers);
    free(wsk->data);
    for(int i=0; i<wsk->quantity_notnumbers; i++) {
        free(wsk->notnumbers[i].characters);
    }
    free(wsk->notnumbers);
    free(wsk);
    
    return pat;
}

void deleteFirst(List_t **head) {
    List_t *wsk = *head;
    
    *head = wsk->next;
    free(wsk->numbers);
    free(wsk->data);
    for(int i=0; i<wsk->quantity_notnumbers; i++) {
        free(wsk->notnumbers[i].characters);
    }
    free(wsk->notnumbers);
    free(wsk);

}

void printResult(List_t *wsk, List_t **head) {
    if(wsk == NULL){
        return;}
    if(wsk->quantity_numbers>0 || wsk->quantity_notnumbers >0)
    fprintf(stdout, "%d", wsk->no);
    List_t *ptr = wsk->next;
    List_t *prev = wsk;

    while (ptr != NULL) {
            if(ptr->comment || ptr->incorrect || ptr->blank ) {
            List_t *nast = ptr->next;
            prev->next = deleteNode(ptr);
            ptr = nast;
            }

            else if (!ptr->comment && !ptr->incorrect && !ptr->blank 
            && compareNumbers(wsk, ptr) 
	    && compareNotnumber_ts(wsk,ptr)) {
                
                fprintf(stdout, " %d", ptr->no);
               
		List_t *nast = ptr->next;
                prev->next = deleteNode(ptr);
                ptr = nast;
            }
            else {
                ptr = ptr->next;
                prev = prev->next;
            }

        }
        if(wsk->quantity_numbers>0 || wsk->quantity_notnumbers >0)
        fprintf(stdout, "\n");

    deleteFirst(head);
    printResult(*head ,head);
}