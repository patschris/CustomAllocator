#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "list.h"
#include "bitvector.h"
#include "declarations.h"

struct ListNode {
    ListNode *prev;         // pointer to previous node
    ListNode *next;         // pointer to next node
    List *head;             // pointer to list's head (in order to get the size)
    void *page;             // page's address given by the bank
    char vec[VECTOR_SIZE];  // bit vector for dirty pages
};

struct List {
    ListNode *first; // pointer of first node
    int size; // class size (32, 64, 128, 256, 512, 1024, 2048, 4096)
};

/* 
    Create a list of class s without any node 
*/
List* createList (int s) {
    List *l;
    if ((l = (List *) malloc(sizeof(List)))== NULL) {
        perror("cannot allocate memory for list at createList function");
        exit(-1);
    }
    l->first = NULL;
    l->size = s;
    return l;  
}

/*  
    Return memory of a page of a specific class. If there is no available memory, ask bank to give another page.
*/
void* giveMem (List *l, ListNode **toret) {
    int i;
    void *p;    
    ListNode *temp = l->first;
    while(temp != NULL) {
        for (i=0; i< (PAGE_SIZE/l->size); i++) {
            /* Checking if there is a non-dirty segment in any page of this class */
            if (!getBit(temp->vec, i)) {
                setBit(temp->vec,i);
                p = temp->page + l->size*i;
                /* mark as first the page with available memory */
                if (temp!=l->first) makeFirst(l,temp);
                *toret = l->first;                
                return p;        
            }
        } 
        temp = temp->next;
    }
    /* If all segments of the page are dirty, ask for another page */
    p = getMem();
    insertAtStart(l,p);
    setBit(l->first->vec,0);
    *toret = l->first;
    return p;
}

/* 
    Insert a new node at the first place of the list 
*/
void insertAtStart (List *l, void *p) {
    ListNode *temp;
    if ((temp = (ListNode*) malloc(sizeof(ListNode))) == NULL) {
        printf("Malloc error in insert at start\n");
        exit(-1);
    }
    temp -> prev = NULL;
    temp -> next = l->first;
    temp -> head = l;
    temp-> page = p;
    memset(temp->vec, 0, VECTOR_SIZE * sizeof(char));
    if (l->first != NULL) l->first->prev = temp;
    l->first = temp;
}

/* 
    Place the node n in the first position in the list 
*/
void makeFirst (List *l, ListNode *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    n->prev = NULL;
    n->next = l->first;
    l->first->prev = n;
    l->first = n;
}

/* 
    Clear the proper bit when myfree is called 
*/
void clearBitFromBitVector (ListNode *ln, void *p) {
    int index = (int)((unsigned long long)p % PAGE_SIZE) / ln->head->size;
    clearBit(ln->vec, index); 
}

/* 
    Delete the first node of the list 
*/
void deleteFirst (List *l) {
    ListNode *todel = l->first;
    l->first = todel->next;
    if (l->first) l->first->prev = NULL;
    free(todel);
}

/* 
    Destroy the list 
*/
void destroyList (List *l) {
    while (l->first != NULL) deleteFirst(l);
    free(l);
}

/* 
    Print the list (Debugging)
*/
void printList (List *l) {
    ListNode *temp = l->first;
    printf("-----------------------------\n");
    printf("List of %d bytes\n", l->size);
    while (temp != NULL) {
        printf("Node %p\n", temp);
        printf("page: %llu\n", (unsigned long long)temp->page);
        printf("vector: ");
        printBitVector(temp->vec, PAGE_SIZE/l->size);
        printf("\n");
        temp = temp->next;
    }
    printf("-----------------------------\n");
}