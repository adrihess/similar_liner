#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structures.h"
#include "load.h"
#include "check.h"

#define BASIS_SIZE 8

void getInput(List_t *temp) {
    temp->data_size = 1;
    int data_size = BASIS_SIZE;
    temp->data = malloc(data_size*sizeof(char));
    
    if(temp->data == NULL)
        exit(1);

    int temporary = getchar();

    while(temporary != '\n' && !isEnd(temporary)) {
        
        if(isForbidden((char)temporary) && !isWhiteChar((char)temporary) 
	&& !isEnd(temporary)){
            temp->incorrect=true;
            
        }
        if(!isWhiteChar((char)temporary) && !isForbidden((char)temporary))
            temp->blank = false;
 
        temp->data[temp->data_size-1] = (char)temporary;
        temp->data_size++;
        if(temp->data_size > data_size) {
	data_size = data_size *2;
        temp->data = (char*)realloc(temp->data, data_size * sizeof(char));}
        if(temp->data == NULL)
            exit(1);

        temporary = getchar();
    }

    if(temp->incorrect && !temp->comment)
        fprintf(stderr, "ERROR %d\n", temp->no);

    temp->data[temp->data_size-1] = (char)temporary;

    
}

void getLines(List_t **head, List_t **ptrr) {
    int temporary = 0;
    int no = 1;
    bool is_comment = false;

    while(temporary != EOF) {

        temporary = getchar();
        if(temporary == EOF)
            break;
        else if(temporary == '#')
            is_comment=true;

        else
            ungetc(temporary, stdin);

        List_t *temp = (List_t*)malloc(sizeof(List_t));
        if(temp == NULL)
            exit(1);


        temp->notnumbers=NULL;
        temp->quantity_notnumbers=0;
        temp->data=NULL;
        temp->data_size=0;
        temp->numbers=NULL;
        temp->quantity_numbers=0;
        temp->no=0;

        if(is_comment){
            temp->comment=true;
            is_comment=false;
        }
        else
            temp->comment=false;

        temp->no = no;
        no++;
        if(*head == NULL)
            *head = temp;
        else {
            (*ptrr)->next = temp;}
        *ptrr = temp;
        temp->incorrect=false;
        temp->blank=true;

        getInput(temp);

    }
}