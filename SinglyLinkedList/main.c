#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "SinglyLinkedList.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);
int comp(void *elementA, void *elementB);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {

#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 6;
    int numOfValues = 5;
    
    printf("=== start [%s] ===\n", __func__);
    
    SLL_t *list = createSLList();
    
    for (int retry=0; retry<testCount; retry++) {
        printf("*** [Test #%d] ***\n", retry+1);
        
        SLLC_t *cell = NULL;
        Element_t *element = NULL;
        switch (retry) {
            case 0:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    insertSLList(list, element);
                    printf("insert : %d\n", element->value);
                }
                cell = findHeadOnSLList(list);
                while (cell != NULL) {
                    printf("find next : %d\n", ((Element_t *)getElementOnSLList(cell))->value);
                    cell = findNextOnSLList(cell);
                }
                while (!isEmptySLList(list)) {
                    element = pullSLList(list);
                    printf("pull : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 1:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    insertAtHeadOnSLList(list, element);
                    printf("insert Head : %d\n", element->value);
                }
                while (!isEmptySLList(list)) {
                    element = pullHeadOnSLList(list);
                    printf("pull Head : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 2:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    insertAtTailOnSLList(list, element);
                    printf("insert Tail : %d\n", element->value);
                }
                while (!isEmptySLList(list)) {
                    element = pullHeadOnSLList(list);
                    printf("pull Head : %d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 3:
                srand((unsigned) time(NULL));
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(rand());
                    insertAtHeadOnSLList(list, element);
                    printf("insert Head : %d\n", element->value);
                }
                
                Element_t *min = findMinOnSLList(list, comp);
                printf("min value : %d\n", min->value);
                Element_t *max = findMaxOnSLList(list, comp);
                printf("max value : %d\n", max->value);
                
                int s1 = max->value;
                Element_t *e1 = createElement(s1);
                element = findElementOnSLList(list, comp, e1);
                if (element != NULL) {
                    printf("found value %d.\n", element->value);
                }
                else {
                    printf("could not found value %d. (T^T)\n", s1);
                }
                free(e1);
                
                int s2 = INT_MAX;
                Element_t *e2 = createElement(s2);
                element = findElementOnSLList(list, comp, e2);
                if (element != NULL) {
                    printf("found value %d.\n", element->value);
                }
                else {
                    printf("could not found value %d. (T^T)\n", s2);
                }
                free(e2);

                // *************************************
                retry = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
    
    destroySLList(list, SLL__WITH_ELEMENT);
    
    printf("=== end [%s] ===\n", __func__);
}

Element_t *createElement(int value) {
    Element_t *element = malloc(sizeof(Element_t));
    if (element == NULL) return NULL;
    element->value = value;
    return element;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

int comp(void *elementA, void *elementB) {
    int valueA = ((Element_t *)elementA)->value;
    int valueB = ((Element_t *)elementB)->value;
    return valueA - valueB;
}
