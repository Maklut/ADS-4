// Copyright 2021 NNTU-CS
#include <algorithm>

int countPairs1(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; ++i) {
    for (int j = i + 1; j < len; ++j) {
      if (arr[i] + arr[j] == value) {
        ++count;
      }
    }
  }
  return count;
}

int countPairs2(int *arr, int len, int value) {
  int count = 0;
  int left = 0;
  int right = len - 1;
  while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == value) {
      if (arr[left] == arr[right]) {
        int n = right - left + 1;
        count += n * (n - 1) / 2;
        break;
      } else {
        int left_val = arr[left];
        int right_val = arr[right];
        int left_count = 0;
        int right_count = 0;
        while (left < len && arr[left] == left_val) {
          ++left_count;
          ++left;
        }
        while (right >= 0 && arr[right] == right_val) {
          ++right_count;
          --right;
        }
        count += left_count * right_count;
      }
    } else if (sum < value) {
      ++left;
    } else {
      --right;
    }
  }
  return count;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; ++i) {
    int target = value - arr[i];
    int left = i + 1;
    int right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] == target) {
        ++count;
        int k = mid + 1;
        while (k < len && arr[k] == target) {
          ++count;
          ++k;
        }
        break;
      } else if (arr[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }
  return count;
}
