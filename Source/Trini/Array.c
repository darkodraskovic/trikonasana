#include <stdio.h>
#include <stdlib.h>
#include "Array.h"

void* arrAlloc(void* array, int count, int itemSize) {
    if (array == NULL) {
        int *base = (int *)malloc((sizeof(int) * 2) + (itemSize * count));
        base[0] = count; // capacity
        base[1] = 0;     // occupied
        return base + 2; // logical index 0
    } else if (ARRAY_LENGTH(array) + count <= ARRAY_CAPACITY(array)) {
        return array;
    } else {
        int demandedSize = ARRAY_LENGTH(array) + count;
        int doubleSize = ARRAY_CAPACITY(array) * 2;
        int capacity = demandedSize > doubleSize ? demandedSize : doubleSize;
        int rawSize = sizeof(int) * 2 + itemSize * capacity;
        int *base = (int *)realloc(ARRAY_RAW_DATA(array), rawSize);
        base[0] = capacity;
        return base + 2;
    }
}

void* arrCreate(int count, int itemSize) {
    return arrAlloc(NULL, count, itemSize);
};

int arrLen(void* array) {
    return (array != NULL) ? ARRAY_LENGTH(array) : 0;
}

int arrCap(void* array) {
    return (array != NULL) ? ARRAY_CAPACITY(array) : 0;
}

void arrDestroy(void* array) {
    if (array != NULL) {
        free(ARRAY_RAW_DATA(array));
    }
}
