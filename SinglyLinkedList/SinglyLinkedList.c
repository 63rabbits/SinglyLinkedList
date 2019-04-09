#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "SinglyLinkedList.h"

//////////////////////////////////////////////////
SLL_t *createSLList() {
    SLL_t *list = malloc(sizeof(SLL_t));
    if (list == NULL) return NULL;
    
    list->head = NULL;
    list->tail = NULL;
    return list;
}

bool destroySLList(SLL_t *list, int option) {
    //  Block illegal parameters.
    if (list == NULL) return false;
    
    clearSLList(list, option);
    free(list);
    return true;
}

bool clearSLList(SLL_t *list, int option) {
    // Block illegal parameters.
    if (list == NULL) return false;
    
    while (!isEmptySLList(list)) {
        void *element = pullSLList(list);
        if ((option == SLL__WITH_ELEMENT) &&
            (element != NULL)) {
            free(element);
        }
    }
    
    return true;
}

bool insertSLList(SLL_t *list, void *elemet) {
    return insertAtTailOnSLList(list, elemet);
}

bool insertAtHeadOnSLList(SLL_t *list, void *element) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (element == NULL) return false;
    
    SLLC_t *cell = createCellOnSLList(element);
    if (cell == NULL) return false;
    
    if (list->head == NULL) {
        cell->next = NULL;
        list->head = cell;
        list->tail = cell;
    }
    else {
        cell->next = list->head;
        list->head = cell;
    }
    
    return true;
}

bool insertAtTailOnSLList(SLL_t *list, void *element) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (element == NULL) return false;
    
    SLLC_t *cell = createCellOnSLList(element);
    if (cell == NULL) return false;
    
    if (list->tail == NULL) {
        cell->next = NULL;
        list->head = cell;
        list->tail = cell;
    }
    else {
        cell->next = NULL;
        list->tail->next = cell;
        list->tail = cell;
    }
    
    return true;
}

void *pullSLList(SLL_t *list) {
    return pullHeadOnSLList(list);
}

void *pullHeadOnSLList(SLL_t *list) {
    if (list == NULL) return NULL;
    if (isEmptySLList(list)) return NULL;
    
    SLLC_t *cell = list->head;
    list->head = cell->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    
    void *element = getElementOnSLList(cell);
    free(cell);
    return element;
}

SLLC_t *findHeadOnSLList(SLL_t *list) {
    // Block illegal parameters.
    if (list == NULL) return NULL;
    
    return list->head;
}

SLLC_t *findTailOnSLList(SLL_t *list) {
    // Block illegal parameters.
    if (list == NULL) return NULL;
    
    return list->tail;
}

SLLC_t *findNextOnSLList(SLLC_t *cell) {
    // Block illegal parameters.
    if (cell == NULL) return NULL;
    
    return cell->next;
}

void *findElementOnSLList(SLL_t *list, int (*comp)(void*, void*), void *element) {
    // Block illegal parameters.
    if (isEmptySLList(list)) return NULL;
    
    SLLC_t *cell = findHeadOnSLList(list);
    while (cell != NULL) {
        int check = (*comp)(cell->element, element);
        if (check == 0) {
            return cell->element;
        }
        cell = findNextOnSLList(cell);
    }
    return NULL;
}

void *findMinOnSLList(SLL_t *list, int (*comp)(void*, void*)) {
    // Block illegal parameters.
    if (isEmptySLList(list)) return NULL;
    
    SLLC_t *cell = findHeadOnSLList(list);
    SLLC_t *min = cell;
    while (cell != NULL) {
        int check = (*comp)(min->element, cell->element);
        if (check > 0) {
            min = cell;
        }
        cell = findNextOnSLList(cell);
    }
    return min->element;
}

void *findMaxOnSLList(SLL_t *list, int (*comp)(void*, void*)) {
    // Block illegal parameters.
    if (isEmptySLList(list)) return NULL;

    SLLC_t *cell = findHeadOnSLList(list);
    SLLC_t *max = cell;
    while (cell != NULL) {
        int check = (*comp)(max->element, cell->element);
        if (check < 0) {
            max = cell;
        }
        cell = findNextOnSLList(cell);
    }
    return max->element;
}

SLL_t *margeSLList(SLL_t *left, SLL_t *right) {
    SLL_t *marge = createSLList();
    
    // move left list into marge list.
    if (left != NULL) {
        marge->head = left->head;
        marge->tail = left->tail;
        left->head = NULL;
        left->tail = NULL;
    }
    
    // marge right list.
    if (!isEmptySLList(right)) {
        marge->tail->next = right->head;
        marge->tail = right->tail;
        right->head = NULL;
        right->tail = NULL;
    }
    
    return marge;
}

bool isEmptySLList(SLL_t *list) {
    if (list == NULL) return true;
    if (list->head == NULL) return true;
    return false;
}

SLLC_t *createCellOnSLList(void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    SLLC_t *cell = malloc(sizeof(SLLC_t));
    if (cell == NULL) return NULL;

    cell->element = element;
    cell->next = NULL;
    
    return cell;
}

bool destroyCellOnSLList(SLLC_t *cell) {
    // Block illegal parameters.
    if (cell == NULL) return false;
    free(cell);
    return true;
}

void *getElementOnSLList(SLLC_t *cell) {
    // Block illegal parameters.
    if (cell == NULL) return NULL;
    
    return cell->element;
}

