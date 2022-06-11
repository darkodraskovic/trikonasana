#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "Trini/Array.h"
#include "Trini/Vector.h"

void testArray() {
  int count = 100;

  // test arrPush
  int* intArr = NULL;
  for (int i = 1; i < count; ++i) {
    arrPush(intArr, i);
    assert(intArr[i - 1] == i);
    int len = arrSize(intArr);
    assert(len == i);
    int cap = pow(2, ceil(log2(i)));
    assert(arrCap(intArr) == cap);
  }

  // test arrAppend
  int len = arrSize(intArr);
  arrAppend(intArr, intArr, len);
  len *= 2;
  assert(arrSize(intArr) == len);
  assert(arrCap(intArr) >= len);
  for (int i = 0; i < len; i++) {
    int j = (i < len / 2 ? i : (i - len / 2)) + 1;
    assert(intArr[i] == j);
  }

  int* intArr2 = NULL;
  arrAppend(intArr2, intArr, len);
  assert(arrSize(intArr2) == len);
  assert(arrCap(intArr2) == len);

  // test arrCreate
  int* floatArr = arrCreate(count, sizeof(float));
  assert(arrSize(floatArr) == 0);
  assert(arrCap(floatArr) == count);
  for (int i = 1; i < count; ++i) {
    arrPush(floatArr, i);
    assert(floatArr[i - 1] == i);
    int len = arrSize(floatArr);
    assert(len == i);
    assert(arrCap(floatArr) == 100);
  }
}

void testVec() {}

// Application
#ifdef __MINGW32__
int WinMain(int argc, char* argv[]) {
#elif _WIN64
int wmain(int argc, char* argv[]) {
#elif __linux__
int main(int argc, char* argv[]) {
#endif

  testArray();

  return 0;
}
