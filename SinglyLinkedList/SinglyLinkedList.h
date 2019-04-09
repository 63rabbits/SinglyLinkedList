#ifndef SinglyLinkedList_h
#define SinglyLinkedList_h

#include <stdbool.h>

//////////////////////////////////////////////////
#define SLL__NO_OPTION 0
#define SLL__WITH_ELEMENT 1

typedef struct SinglyLinkedList_Cell {
    void *element;
    struct SinglyLinkedList_Cell *next;
} SLLC_t;

typedef struct SinglyLinkedList {
    SLLC_t *head;
    SLLC_t *tail;
} SLL_t;

//////////////////////////////////////////////////
SLL_t *createSLList(void);
bool destroySLList(SLL_t *list, int option);
bool clearSLList(SLL_t *list, int option);
bool insertSLList(SLL_t *list, void *element);
bool insertAtHeadOnSLList(SLL_t *list, void *element);
bool insertAtTailOnSLList(SLL_t *list, void *element);
void *pullSLList(SLL_t *list);
void *pullHeadOnSLList(SLL_t *list);
SLLC_t *findHeadOnSLList(SLL_t *list);
SLLC_t *findTailOnSLList(SLL_t *list);
SLLC_t *findNextOnSLList(SLLC_t *cell);
void *findElementOnSLList(SLL_t *list, int (*comp)(void*, void*), void *element);
void *findMinOnSLList(SLL_t *list, int (*comp)(void*, void*));
void *findMaxOnSLList(SLL_t *list, int (*comp)(void*, void*));
SLL_t *margeSLList(SLL_t *left, SLL_t *right);
bool isEmptySLList(SLL_t *list);
SLLC_t *createCellOnSLList(void *element);
bool destroyCellOnSLList(SLLC_t *cell);
void *getElementOnSLList(SLLC_t *cell);

#endif
