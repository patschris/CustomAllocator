#include <stdio.h>
#include <limits.h>
#include "declarations.h"

/*  
    References:
        1) http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html 
        2) https://stackoverflow.com/questions/42841264/print-out-bit-in-int-array
*/

/* 
    Set bit b to 1
*/
void setBit (char *v, int b) {
    v[b/CHAR_BIT] |= 1 << (b % CHAR_BIT);
}

/* 
    Set bit b to 0 
*/
void clearBit (char *v, int b) {
    v[b/CHAR_BIT] &= ~(1 << (b % CHAR_BIT));
}

/* 
    Get the value of the bit b 
*/
int getBit(char *v, int b) {
    return ((v[b/CHAR_BIT] >> (b%CHAR_BIT)) & 1);
}

/* 
    Print bit vector of size s 
*/
void printBitVector(char *v, int s) {
    int i;
    for (i=0; i < s; i++) printf("%d", getBit(v,i));
    printf("\n");
}