#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "check.h"
#include "structures.h"

#define BASIS_SIZE 8
#define ASCII_CORRECTION 32
#define MIN_SIGN 65
#define MAX_SIGN 90
#define HEX 16
#define DEC 10
#define OCT 8

 void sortNumbers(List_t *wsk) {
    if(wsk->quantity_numbers <2)
        return;

    for(int i=0; i<wsk->quantity_numbers; i++) {
        for(int j=0; j<wsk->quantity_numbers-1-i;j++) {
            if(wsk->numbers[j] > wsk->numbers[j+1]) {
                long double temp = wsk->numbers[j];
                wsk->numbers[j] = wsk->numbers[j+1];
                wsk->numbers[j+1] = temp;
            }
        }
    }
}

char* increaseNotnumTab(char *temp_nan, int *data_size, char sign, int *pot_data_size) {
    if(temp_nan == NULL) {
        *data_size = 1;
        *pot_data_size = BASIS_SIZE;
        char *temp = (char*)malloc(*pot_data_size*sizeof(char));
        
	if(temp == NULL)
            exit(1);

        return temp;
    }

    *data_size = *data_size+1;
    if( *data_size > *pot_data_size) {
    *pot_data_size = *pot_data_size *2;
    
    temp_nan = (char*)realloc(temp_nan, *pot_data_size * sizeof(char));}
    if(temp_nan == NULL)
        exit(1);

    if((int)sign >= MIN_SIGN && (int)sign <= MAX_SIGN) {
        sign +=ASCII_CORRECTION;
    }

    temp_nan[*data_size-1] = sign;
    return temp_nan;
}
void insertNan(char *temp_nan, int data_size, List_t *wsk) {

    if(wsk->notnumbers == NULL) {
    wsk->max_quantity_notnumbers=BASIS_SIZE;
    wsk->notnumbers = 
   (Notnumber_t *)malloc(wsk->max_quantity_notnumbers * sizeof(Notnumber_t));
        if(wsk->notnumbers == NULL)
            exit(1);
        wsk->quantity_notnumbers=1;
    }

    else {
        wsk->quantity_notnumbers = wsk->quantity_notnumbers + 1;
	if(wsk->quantity_notnumbers > wsk->max_quantity_notnumbers) {
	wsk->max_quantity_notnumbers = wsk->max_quantity_notnumbers *2;
        wsk->notnumbers = 
       (Notnumber_t *)realloc(wsk->notnumbers, wsk->data_size * sizeof(Notnumber_t));}
        if(wsk->notnumbers == NULL)
            exit(1);
    }

    Notnumber_t new_nan;
    new_nan.notnumber_size = data_size;
    new_nan.characters = temp_nan;

    wsk->notnumbers[wsk->quantity_notnumbers-1] = new_nan; 
}

//sortuje liczby po ich rozmiarze oraz leksykogramatycznie jak są
//tych samych rozmiarów
void sortNotnumbers(List_t *wsk) {

    for(int i=0; i<wsk->quantity_notnumbers; i++) {
        for(int j=0; j<wsk->quantity_notnumbers-1-i;j++) {
            if(wsk->notnumbers[j].notnumber_size > wsk->notnumbers[j+1].notnumber_size) {
                Notnumber_t temp = wsk->notnumbers[j];
                wsk->notnumbers[j] = wsk->notnumbers[j+1];
                wsk->notnumbers[j+1] = temp;
            }
        }
    }

    for(int i=0; i<wsk->quantity_notnumbers; i++) {
        for(int j=0; j<wsk->quantity_notnumbers-1-i;j++) {

            if(wsk->notnumbers[j].notnumber_size == wsk->notnumbers[j+1].notnumber_size) {

                for(int poz=0; poz<wsk->notnumbers[j].notnumber_size; poz++) {
                    if (wsk->notnumbers[j].characters[poz] > wsk->notnumbers[j+1].characters[poz]) {
                        Notnumber_t temp = wsk->notnumbers[j];
                        wsk->notnumbers[j] = wsk->notnumbers[j+1];
                        wsk->notnumbers[j+1] = temp;
		        break;
                    }
		    else if(wsk->notnumbers[j].characters[poz] 
                       < wsk->notnumbers[j+1].characters[poz])
			break;
                }
            }
        }
    }

}

void increaseNumTab(struct List_t *wsk) {
    if(wsk->numbers == NULL) {
        wsk->quantity_numbers = 1;
	wsk->max_quantity_numbers = BASIS_SIZE;
        wsk->numbers = malloc(wsk->max_quantity_numbers*sizeof(long double));
        if(wsk->numbers == NULL)
            exit(1);

        return;
    }

    wsk->quantity_numbers = wsk->quantity_numbers+1;
    if(wsk->quantity_numbers > wsk->max_quantity_numbers) {
    wsk->max_quantity_numbers = wsk->max_quantity_numbers *2;
    wsk->numbers = 
    (long double*)realloc(wsk->numbers, wsk->max_quantity_numbers * sizeof(long double));}
    if(wsk->numbers == NULL)
        exit(1);
}

bool mightHex(List_t *wsk, int indic) {
    if(wsk->data[indic] == '+' || wsk->data[indic] == '-') {
        if(indic +2 < wsk->data_size) {
            if(wsk->data[indic+1] == '0' && (wsk->data[indic+2] == 'x' 
	    || wsk->data[indic+2] == 'X') )
                return true;
        }
    }
    else {
        if(indic +1 < wsk->data_size) {
            if(wsk->data[indic] == '0' && (wsk->data[indic+1] == 'x' 
	    || wsk->data[indic+1] == 'X'))
                return true;
        }
    }
    return false;

}

void processData(List_t *wsk) {
    while(wsk != NULL) {

        if(!wsk->comment && !wsk->incorrect && !wsk->blank) {


            long double resF = 0.0; 
            long resK = 0; 
            unsigned long int resL = 0; 

            bool is_signed = false;
            bool is_float = false;

            int indic = 0;
            int base = DEC;
            char *temp = NULL;
            char *ptr;

            while(indic < wsk->data_size) {

                while (indic < wsk->data_size && isWhiteChar(wsk->data[indic])) {
                    indic++;
                }
                if(indic == wsk->data_size)
                    break;

                temp = &wsk->data[indic];

                if (wsk->data[indic] == '0') {
                    if (indic + 1 < wsk->data_size && isHex(wsk->data[indic + 1]))
                        base = HEX;
                    else
                        base = OCT;
                } else if (wsk->data[indic] == '-') {
                    is_signed = true;
                    base = DEC;


                } else
                    base = DEC;

                if(indic+2 < wsk->data_size && wsk->data[indic] =='0' 
                && isHex(wsk->data[indic+1]) && isWhiteChar(wsk->data[indic+2])) {
                    resL = 0;
                    indic = indic+2;
                    ptr = temp + 2;
                }

                else if (is_signed)
                    resK = strtol(temp, &ptr, base);
                else
                    resL = strtoul(temp, &ptr, base);


                if(( ptr == temp || !isWhiteChar(*ptr) )&& !mightHex(wsk, indic)) {

                    resF = strtold(temp, &ptr);
                    is_float = true;}


                if(ptr!= temp && *ptr != '\0' && !isnan(resF) && isWhiteChar(*ptr)) {
                    
                    increaseNumTab(wsk);
                   

                    if(is_signed&&!is_float)
                        wsk->numbers[wsk->quantity_numbers -1] = (long double)resK;
                    else if(!is_float)
                        wsk->numbers[wsk->quantity_numbers -1] = (long double)resL;
                    else if(is_float)
                        wsk->numbers[wsk->quantity_numbers -1] = resF;

                    indic = indic + (int)(ptr - temp);
                    temp = ptr;

                }

                else if(*ptr != '\0' && !isWhiteChar(wsk->data[indic]) 
                && !isForbidden(wsk->data[indic]) && !isEnd(wsk->data[indic])){
                    bool end = false;

                    int data_size = 0;
                    int pot_data_size = 0;
                    char *temp_nan = increaseNotnumTab(NULL, &data_size, wsk->data[indic], &pot_data_size);

                    if((int)wsk->data[indic] >= 65 && (int)wsk->data[indic] <= 90) {
                        temp_nan[0] = (char)(wsk->data[indic] + 32);

                    }
                    else
                        temp_nan[0] = wsk->data[indic];

                    indic++;
                    while(indic < wsk->data_size && !isWhiteChar(wsk->data[indic]) 
		    && !isEnd(wsk->data[indic])) {
                        

			if(isWhiteChar(wsk->data[indic]) || isForbidden(wsk->data[indic]))
                            end = true;

                        if(!end) {
                            temp_nan = 
                            increaseNotnumTab(temp_nan, &data_size, wsk->data[indic], &pot_data_size);
                        }
                        indic++;
                    }
                    insertNan(temp_nan, data_size, wsk);
                }
                else {
                    while(indic < wsk->data_size && (isWhiteChar(wsk->data[indic]) 
                    || isEnd(wsk->data[indic])) ) {

                        indic++;
                    }
                }

                is_float = false;
                is_signed=false;

            }
            sortNotnumbers(wsk);
            sortNumbers(wsk);
        }
        wsk = wsk->next;

    }
}