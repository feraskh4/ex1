#include "RLEList.h"
#include <string.h>

#define DEFAULT_EXPORTED_LINE_LENGTH 4

struct RLEList_t{
    char value;
    int amount;
    struct RLEList_t* next;
};

//implement the functions here
RLEList RLEListCreate() {
    RLEList ptr = malloc(sizeof(*ptr));
    if (!ptr) {
        return NULL;
    }
    ptr->value = 0;
    ptr->next =NULL;
    return ptr;
}

void RLEListDestroy(RLEList list) {
    RLEList ptr, store;
    ptr = list;
    while (ptr) {
        store = ptr->next;
        free(ptr);
        ptr = store;
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (!list || !value) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList ptr = list;
    while (ptr->next) {
        ptr = ptr->next;
    }
    if (ptr->amount==0) {
        ptr->value = value;
        ptr->amount = 1;
        return RLE_LIST_SUCCESS;
    }
    if (ptr->value==value) {
        ptr->amount += 1;
        return RLE_LIST_SUCCESS;
    }
    RLEList newHead = RLEListCreate();
    if (!newHead) {
           return RLE_LIST_OUT_OF_MEMORY;
    }
    newHead->value = value;
    newHead->amount = 1;
    ptr->next = newHead;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    if (!list) {
        return -1;
    }
    int count = 0;
    while (list) {
        count += list->amount;
        list = list->next;
    }
    return count;
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list) {
           return RLE_LIST_NULL_ARGUMENT;
    }
    if (RLEListSize(list)<index||RLEListSize(list)==0) {
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList ptr = list, ptrNext;
    //if count is not positive that means the char is in this node
    int count=index;
    count -= ptr->amount;
    while (count>0) {
        ptr = ptr->next;
        count -= ptr->amount;
    }
    if (index==0) {
        if (list->next) {
            if (list->amount==1)
                 list = list->next;
            else list->amount -= 1;
            return RLE_LIST_SUCCESS;
        }
        if(list->amount==1)
            list = NULL;
        else list->amount -= 1;
        return RLE_LIST_SUCCESS;
    }
    //ptrNext is the pointer to the index we want to remove
    ptrNext = ptr->next;
    if (ptrNext->next) {
        if (ptrNext->amount==1)
             ptr->next = ptrNext->next;
        else ptrNext->amount -= 1;
        return RLE_LIST_SUCCESS;
    }
    if (ptrNext->amount==1)
    ptr->next = NULL;
    else ptrNext->amount -= 1;
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if (RLEListSize(list) <= index || index < 0) {
        if (result) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    RLEList ptr = list;
    
    while (ptr && ptr->amount <= index) {
        index -= ptr->amount;
        ptr = ptr->next;
    }
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return ptr->value;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (!list) {
        return  RLE_LIST_NULL_ARGUMENT;
    }
    RLEList new_list = RLEListCreate(), ptr = list;

    char current_char;
    while (ptr) {
        for (int i = 1; i <= ptr->amount; i++) {
            current_char = ptr->value;
            RLEListAppend(new_list, map_function(current_char));
        }
        ptr = ptr->next;
    }
    RLEListDestroy(list);
    list = new_list;
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    RLEList list_ptr = list;
    char *out = malloc(sizeof(*out) * RLEListSize(list) * DEFAULT_EXPORTED_LINE_LENGTH + 1);
    char *out_ptr = out;
    int cur_line_length;

    while (list_ptr) {
        cur_line_length = sprintf(out_ptr, "%c%d\n", list_ptr->value, list_ptr->amount);
        out_ptr += cur_line_length;
        list_ptr = list_ptr->next;
    }
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return out;
}