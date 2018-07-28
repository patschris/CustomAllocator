#ifndef _hashmap_
#define _hashmap_

typedef struct Hashnode Hashnode;
typedef struct Hashmap Hashmap;

Hashmap *createHashmap(void);
void insertHashnode(Hashmap *, ListNode *, void *);
void deleteHashnode(Hashmap *);
void destroyHashmap(Hashmap *);
ListNode *search(Hashmap *,void *);
int hashFunction(void *);
void printHashTable (Hashmap **, int);

#endif
