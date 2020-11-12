#include <iostream>
using namespace std;

int midpoint(int min, int max) {
  return min + (max - min) / 2;
}

/**
 * Binary Search without Recursion
 * @param val - Value to Search for
 * @param arr - The Array to Search in
 * @param min - The Lower Bound of the Array
 * @param max - The Upper Bound of the Array
 * @returns Index of the Value or -1 if not found
 */
int binarySearch(int val, int arr[], int min, int max) {
  int _min = min;
  int _max = max;
  int mid = midpoint(min, max);

  while (_min + 1 < _max) {
    // Value Found?
    if (val == arr[mid]) {
      return mid;
    }

    // Left side
    else if (val < arr[mid]) {
      _max = mid;
    } 
    
    // Right Side
    else {
      _min = mid;
    }

    // New Midpoint
    mid = midpoint(_min, _max);
  }

  // Not Found
  return  -1;
}

/**
 * Recursive Binary Search
 * @param val - Value to Search for
 * @param arr - The Array to Search in
 * @param min - The Lower Bound of the Array
 * @param max - The Upper Bound of the Array
 * @returns Index of the Value or -1 if not found
 */
int binarySearch_recursed(int val, int arr[], int min, int max) {
  int mid = midpoint(min, max);

  // Found
  if (val == arr[mid]) {
    return mid;
  }

  // Reached the End :(
  else if (min + 1 == max) {
    return -1;
  }

  // Left Search
  else if (val < arr[mid]) {
    return binarySearch_recursed(val, arr, min, mid);
  }

  // Right Search
  else {
    return binarySearch_recursed(val, arr, mid, max);
  }
}

int main() {
  int arr[] = {1, 5, 6, 7, 19, 23, 45, 99, 192, 291, 292};
  int size = sizeof(arr) / sizeof(arr[0]);

  // Test Case
  int test[] = {0, 1, 4, 5, 6, 7, 8, 19, 20, 23, 24, 45, 50, 99, 100, 192, 200, 291, 292, 300};
  int testSize = sizeof(test) / sizeof(test[0]);


  // Test to Find all
  for (int i =0; i < testSize; i++) {
    int res = binarySearch_recursed(test[i], arr, 0, size);

    printf("Value '%d' is at index[%d]\n", test[i], res);
  }
  
  return 0;
}