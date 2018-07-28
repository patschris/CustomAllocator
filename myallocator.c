#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hashmap.h"
#include "declarations.h"

/********** Global variables **********/
/**/    int first_time = 0;         /**/
/**/    List *array[8];             /**/
/**/ Hashmap *hashArray[HASH_SIZE]; /**/
/*************************************/

/* 
    Initialize all the necessary data structures for my allocator 
*/
void initDataStructures (void) {
    int i;
    for (i=0; i<8; i++) {
        if ((array[i]=createList(2<<(i+4))) == NULL) {
            printf("Error in the allocation of the data structures\n");
            exit(-1);
        }
    }
    for(i=0;i<HASH_SIZE;i++) {
        if ((hashArray[i] = createHashmap())==NULL) {
            printf("Error in the allocation of the data structures\n");
            exit(-1);
        }
    }
}

/* 
    Custom malloc implementation 
*/
void* mymalloc (size_t cbytes) {
    void *p = NULL;
    ListNode *ln = NULL;
    int t=0, i, index;
    /* Initialize data structures if they are uninitialized */
    if (!first_time) {
        initDataStructures();
        first_time = 1;
    }
    for (i=0; i<8; i++) {
        if (cbytes <= (2<<(i+4))) {
            p = giveMem(array[i], &ln); // ask for a new page
            index = hashFunction(p);
            insertHashnode(hashArray[index], ln, p); // insert the page to the hashtables
            t=1;
            break;
        }
    }
    if (!t) {
        if ((p = malloc(cbytes))== NULL) { // if cbytes > 4096, call malloc
            perror("call system's malloc failed in mymalloc");
            exit(-1);
        }
    }
    return p;
}

/*
    Custom free implementation
*/
void myfree(void *p) {
    /* Initialize data structures if they are uninitialized */
    if (!first_time) {
        initDataStructures();
        first_time = 1;
    }
    /* I am going to search in the list which is in the index position of the hashArray */
    int index = hashFunction(p);
    ListNode *ln = search(hashArray[index],p);
    if (ln== NULL) {
        free(p); // the page is not in my data structures (calling free)
    }
    else {
        clearBitFromBitVector(ln, p); // if the page is in my data structures, clear the proper bit
    }
}

/* 
    Clean all data structures after the program exits 
*/
void clean (void) {
    int i;
    if (first_time) {
        for (i=0; i<8; i++) destroyList(array[i]);
        for (i=0;i<HASH_SIZE;i++) destroyHashmap(hashArray[i]);
    }
}
