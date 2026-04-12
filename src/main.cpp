// Copyright 2021 NNTU-CS
#include <iostream>
#include "alg.h"

int main() {
  int arr[] = {20, 30, 30, 40, 40};
  int len = 5;
  int value = 50;
  
  std::cout << countPairs1(arr, len, value) << std::endl;
  std::cout << countPairs2(arr, len, value) << std::endl;
  std::cout << countPairs3(arr, len, value) << std::endl;
  
  return 0;
}
