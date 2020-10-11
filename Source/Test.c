#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "Trini/Array.h"

void testArray() {
    int count = 100;
    int* intArr = NULL;
    for (int i = 1; i < count; ++i) {
        arrPush(intArr, i);
        assert(intArr[i-1] == i);
        int len = arrLen(intArr);
        assert(len == i);
        int cap = pow(2, ceil(log2(i)));
        assert(arrCap(intArr) == cap);
    }
    
    int* floatArr = arrCreate(count, sizeof(float));
    for (int i = 1; i < count; ++i) {
        arrPush(floatArr, i);
        assert(floatArr[i-1] == i);
        int len = arrLen(floatArr);
        assert(len == i);
        assert(arrCap(floatArr) == 100);
    }    
}
