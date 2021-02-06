#include <bits/stdc++.h>
#include <fmt/format.h>
using namespace std;


inline int midpoint(int low, int high) {
  return floor((high - low) / 2) + low;
}

void merge(int values[], int low, int mid, int high) {
  int temp[high - low];
  int k = 0, i = low, j = mid;

  // Compare both Slices of Array
  while( i < mid && j < high ) {
    if (values[i] <= values[j]) {   // Left < Right
      temp[k++] = values[i++];
    } else {
      temp[k++] = values[j++];
    }
  }

  // Move over rest of the data
  while (i < mid)
    temp[k++] = values[i++];
  while (j < high)
    temp[k++] = values[j++];
  
  // Move over result to Array
  k = 0;
  while ( k < high - low) {
    int index = low + k;
    values[index] = temp[k++];
  }
}

void merge_sort(int low, int high, int arr[]) {
  // Base Case
  int mid = midpoint(low, high);
  if (low == mid) return;
  
  // Left & Right Merge Sort
  merge_sort(low, mid, arr);
  merge_sort(mid, high, arr);
  merge(arr, low, mid, high);
}

void printArr(int arr[], int size) {
  cout << " { ";
  for (int i = 0; i < size; i++) {
    cout << arr[i] << (i == size - 1 ? " " : ", ");
  }
  cout << "}\n";
}

int main() {
  int arr[] = {7, 3, 8, 4, 1, 0};
  const int size = 6;

  printArr(arr, size);
  merge_sort(0, size, arr);
  printArr(arr, size);
  
  return 0;
}