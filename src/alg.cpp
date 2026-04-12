// Copyright 2021 NNTU-CS

int countPairs1(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (arr[i] + arr[j] == value) {
        count++;
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
        int leftVal = arr[left];
        int rightVal = arr[right];
        int leftCount = 0;
        int rightCount = 0;
        while (left < len && arr[left] == leftVal) {
          leftCount++;
          left++;
        }
        while (right >= 0 && arr[right] == rightVal) {
          rightCount++;
          right--;
        }
        count += leftCount * rightCount;
      }
    } else if (sum < value) {
      left++;
    } else {
      right--;
    }
  }
  return count;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    int target = value - arr[i];
    int left = i + 1;
    int right = len - 1;
    int first = -1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (arr[mid] == target) {
        first = mid;
        right = mid - 1;
      } else if (arr[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    if (first != -1) {
      int last = first;
      while (last + 1 < len && arr[last + 1] == target) {
        last++;
      }
      count += (last - first + 1);
    }
  }
  return count;
}
