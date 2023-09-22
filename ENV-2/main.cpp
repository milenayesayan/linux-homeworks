#include <iostream>
#include "complex.h"
#include "sort.h"
int main() {
  int size;
  std::cin >> size;
  Complex arr[size];
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i].real >> arr[i].imag;
  }
  sortingComplex(arr, size);
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i].real << " " << arr[i].imag << " "; 
  }
  return 0;
}