#ifndef _list_
#define _list_

typedef struct ListNode ListNode;
typedef struct List List;

List* createList(int);
void* giveMem(List *, ListNode **);
void insertAtStart(List *, void *);
void makeFirst(List *, ListNode *);
void clearBitFromBitVector(ListNode *, void *);
void deleteFirst (List *);
void destroyList (List *);
void printList(List *);

#endif
