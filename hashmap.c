#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hashmap.h"
#include "declarations.h"

/* 
    Node of Hashmap 
*/
struct Hashnode {
    Hashnode *next; // Next Hashnode of the list
    ListNode *pagenode; // List node that contains the page returned by the bank
    void *page; // Page returned by the bank
};

/* 
    Every entry of the hash array is a hash map that points to a hash Node 
    Hashmap is a list of hash nodes
*/
struct Hashmap {
    Hashnode *first;
};

/* 
    Create a hash map without any entry 
*/
Hashmap *createHashmap (void) {
    Hashmap *h;
    if ((h = (Hashmap *)malloc(sizeof(Hashmap))) == NULL) {
        perror("Cannot allocate a hashmap");
        exit(-1);
    }
    h->first = NULL;
    return h;
}

/* 
    Insert a Hashnode - if it is not already exist - at the last position of the hashmap
*/
void insertHashnode (Hashmap *h, ListNode *ln, void *p) {
    Hashnode *hn, *last;
    if ((hn = (Hashnode *)malloc(sizeof(Hashnode))) == NULL) {
        perror("Cannot allocate a hashnode");
        exit(-1);
    }
    hn->next = NULL;
    hn->pagenode = ln;
    hn->page = p;
    if (h->first == NULL) {
        h->first = hn;
    }
    else {
        last = h->first;
        if(last->page == p) {
            free(hn);
            return;
        }        
        while(last->next != NULL) {
            if(last->page == p) {
                free(hn);
                return;
            }
            last = last->next;
        }
        last->next = hn;
     } 
}

/* 
    Delete the first node of the Hashmap 
*/
void deleteHashnode (Hashmap *h) {
    Hashnode *todel = h->first;    
    h->first = h->first->next;
    free(todel);
}

/* 
    Destroy the hashmap 
*/
void destroyHashmap (Hashmap *h) {
    while (h->first != NULL) deleteHashnode(h);
    free(h);
}

/* 
    Search the listnode(pagenode) where page p is stored
*/
ListNode *search(Hashmap *h, void *p) {
    Hashnode *tofind = h->first;
    while (tofind != NULL){
        if (tofind->page == p) return tofind->pagenode;  
        tofind = tofind->next;
    }
    return NULL;
}

/* 
    Mod Hash function 
*/
int hashFunction(void *addr) {
    return (int) ((unsigned long long)addr % HASH_SIZE);
}

/*
    Print the hash table with the pages (Debugging)
*/
void printHashTable (Hashmap **h, int size) {
    int i;
    Hashnode *temp;
    printf("-----------------------------\n");
    printf("Hashtable\n");
    for (i=0; i<size; i++) {
        temp = h[i]->first;    
        if (temp != NULL) printf("\nBucket %d\n", i);    
        while (temp != NULL) {
            printf("Page %llu is in list node %p\n",(unsigned long long)temp->page, temp->pagenode);
            temp = temp->next;
        }
    }
    printf("-----------------------------\n");
}
