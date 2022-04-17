#include "RLEList.h"
#include <string.h>

struct RLEList_t{
    //TODO: implement
    // DONE!
    char value;
    struct RLEList* next;
};

//implement the functions here
//majd
RLEList RLEListCreate() {
    RLEList ptr = malloc(sizeof(ptr));
    if (!ptr) {
        return NULL;
    }
    ptr->value = ' ';
    ptr->next =NULL;
    return ptr;
}

// feras
void RLEListDestroy(RLEList list) {
    RLEList ptr, store;
    ptr = list;
    while (ptr) {
        store = ptr->next;
        free(ptr);
        ptr = store;
    }
}

//majd
RLEListResult RLEListAppend(RLEList list, char value) {
    if (!list || !value) {
           return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList newHead = RLEListCreate(newHead);
    if (!newHead) {
           return RLE_LIST_OUT_OF_MEMORY;
    }
    newHead->value = value;
    list->next=newHead;
    return RLE_LIST_SUCCESS;
}

// feras
int RLEListSize(RLEList list) {
    if (!list) {
        return -1;
    }
    int count = 0;
    while (list) {
        count++;
        list->next;
    }
    return count;
}

//majd
RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list) {
           return RLE_LIST_NULL_ARGUMENT;
    }
    if (RLEListSize(list)<index) {
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList ptr = list, ptrNext;
    for (int i = 0; i < index-1; i++) {
        ptr = ptr->next;
    }
    ptrNext = ptr->next;
    if (ptrNext->next) {
        ptr->next = ptrNext->next;
        RLEListDestroy(ptrNext);
            return RLE_LIST_SUCCESS;
    }
    ptr->next = NULL;
    RLEListDestroy(ptrNext);
    return RLE_LIST_SUCCESS;
}

// feras
char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    RLEList ptr = list;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
        if (!ptr) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return 0;
        }
    }
    *result = RLE_LIST_SUCCESS;
    return ptr->value;
}

//feras
char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    char counted_char = list->value;
    char *out = malloc(sizeof(out) * 4 * RLEListSize(list)), *out_ptr = out;
    int count = 1, line_length = 0;
    RLEList list_ptr = list->next;

    while (list_ptr) {
        if (list_ptr->value != counted_char) {
            
            // add "<counted_char><count>\n" to out
            counted_char = list_ptr->value;
            count = 1;
        }
        else {
            count++;
        }
        list_ptr = list_ptr->next;
    }
}