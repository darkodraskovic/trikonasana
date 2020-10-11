#ifndef ARRAY_H
#define ARRAY_H

#define ARRAY_RAW_DATA(array) ((int*)(array) - 2)
#define ARRAY_CAPACITY(array) (ARRAY_RAW_DATA(array)[0])
#define ARRAY_LENGTH(array) (ARRAY_RAW_DATA(array)[1])

#define arrPush(array, value)                   \
    array = arrAlloc(array, 1, sizeof(value));  \
    array[arrLen(array)] = value;               \
    ARRAY_LENGTH(array)++;

#define arrAppend(dynArr, cArr, count)                  \
    dynArr = arrAlloc(dynArr, count, sizeof(*cArr));    \
    memcpy(dynArr, cArr, sizeof(*cArr) * count);        \
    ARRAY_LENGTH(dynArr) += count;

void* arrAlloc(void* array, int count, int itemSize);
int arrLen(void* array);
int arrCap(void *array);

void* arrCreate(int count, int itemSize);
void arrDestroy(void* array);

#endif
