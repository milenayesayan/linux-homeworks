#include "sort.h"
//#include "complex.cpp"
void sortingComplex(Complex* arr, int size) {
  for (int i = 0; i < size - 1; ++i) {
    bool flag = 0;
    for (int j = 0; j < size - i - 1; ++j) { 
      if (arr[j].abs() > arr[j + 1].abs()) { 
        Complex temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        flag = 1;
      }
    }
       if(flag == 1) {
         break;
       }
  }
}