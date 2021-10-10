#include <stdio.h>
#include <stdbool.h>
#include "check.h"

#define MIN_LEGALNA 33
#define MAX_LEGALNA 126

bool isWhiteChar(char sign) {
    if(sign == ' ' || sign == '\t' ||sign == '\n' ||sign == '\v' 
    ||sign == '\f' ||sign == '\r')
        return true;
    else
        return false;
}

bool isForbidden(char sign) {
    if(sign<MIN_LEGALNA || sign > MAX_LEGALNA)
        return true;
    else
        return false;
}

bool isEnd(int sign) {
    if(sign == EOF)
        return true;
    else
        return false;
}

bool isHex(char sign){
    if(sign == 'X' || sign == 'x')
        return true;
    else
        return false;
}