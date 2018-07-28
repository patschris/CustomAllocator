#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

/* Align memory to 4096 */
void align (void **s, void **e) {
    if ((unsigned long long)*s % PAGE_SIZE != 0) {
        *s = (void *)(((unsigned long long)*s/PAGE_SIZE + 1)*PAGE_SIZE); 
        *e = *s + (MALLOC_SIZE/PAGE_SIZE-1)*PAGE_SIZE; 
    } 
}

/*  Memory Bank : If there is another page of 4 KB available, 
    return it, otherwise, allocate another 1MB */
void *getMem() {
    static void* start = NULL; // start of the page
    static void* end = NULL; // end of the page
    if (start == end) {
        if ((start = malloc((size_t)MALLOC_SIZE))== NULL) {
            perror("Malloc of bank returned null");
            exit(-1);        
        }
        end = start + MALLOC_SIZE;
        align(&start, &end); // align to 4096
    }
    else {        
        start = start + PAGE_SIZE;  
    }
    return start;
}
