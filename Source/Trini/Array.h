#ifndef ARRAY_H
#define ARRAY_H

#include <string.h>

#define arrPush(array, value) do {                      \
        array = arrAlloc(array, 1, sizeof(value));      \
        array[((int*)(array))[-1]] = value;             \
        ((int*)(array))[-1]++;                          \
    } while(0)

#define arrAppend(array, cArray, count) do {                             \
        array = arrAlloc(array, count, sizeof(*cArray));                \
        memcpy(array + ((int*)(array))[-1], cArray, sizeof(*cArray) * count); \
        ((int*)(array))[-1] += count;                                  \
    } while(0)

void* arrAlloc(void* array, int count, int itemSize);
int arrSize(void* array);
int arrCap(void *array);

void* arrCreate(int count, int itemSize);
void arrDestroy(void* array);

#endif
