#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "Trini/Array.h"

void testArray() {
    int count = 100;

    // test arrPush
    int* intArr = NULL;
    for (int i = 1; i < count; ++i) {
        arrPush(intArr, i);
        assert(intArr[i-1] == i);
        int len = arrLen(intArr);
        assert(len == i);
        int cap = pow(2, ceil(log2(i)));
        assert(arrCap(intArr) == cap);
    }
    
    // test arrAppend
    int len = arrLen(intArr);    
    arrAppend(intArr, intArr, len);
    len *= 2;
    assert(arrLen(intArr) == len);
    assert(arrCap(intArr) >= len);
    for (int i = 0; i < len; i++) {
        int j = (i < len/2 ? i : (i-len/2)) + 1;
        assert(intArr[i] == j);
    }
    
    int* intArr2 = NULL;
    arrAppend(intArr2, intArr, len);
    assert(arrLen(intArr2) == len);
    assert(arrCap(intArr2) == len);

    // test arrCreate
    int* floatArr = arrCreate(count, sizeof(float));
    assert(arrLen(floatArr) == 0);
    assert(arrCap(floatArr) == count);
    for (int i = 1; i < count; ++i) {
        arrPush(floatArr, i);
        assert(floatArr[i-1] == i);
        int len = arrLen(floatArr);
        assert(len == i);
        assert(arrCap(floatArr) == 100);
    }
}