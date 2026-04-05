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
            int leftVal = arr[left];
            int rightVal = arr[right];
            
            if (leftVal == rightVal) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftCount = 1;
                while (left + 1 < right && arr[left + 1] == leftVal) {
                    leftCount++;
                    left++;
                }
                
                int rightCount = 1;
                while (right - 1 > left && arr[right - 1] == rightVal) {
                    rightCount++;
                    right--;
                }
                
                count += leftCount * rightCount;
                left++;
                right--;
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
    
    for (int i = 0; i < len - 1; i++) {
        int target = value - arr[i];
        int first = -1;
        int left1 = i + 1;
        int right1 = len - 1;
        while (left1 <= right1) {
            int mid = left1 + (right1 - left1) / 2;
            if (arr[mid] == target) {
                first = mid;
                right1 = mid - 1;
            } else if (arr[mid] < target) {
                left1 = mid + 1;
            } else {
                right1 = mid - 1;
            }
        }
        
        if (first != -1) {
            int last = -1;
            int left2 = i + 1;
            int right2 = len - 1;
            while (left2 <= right2) {
                int mid = left2 + (right2 - left2) / 2;
                if (arr[mid] == target) {
                    last = mid;
                    left2 = mid + 1;
                } else if (arr[mid] < target) {
                    left2 = mid + 1;
                } else {
                    right2 = mid - 1;
                }
            }
            
            count += (last - first + 1);
        }
    }
    
    return count;
}
