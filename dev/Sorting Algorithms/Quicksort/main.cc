#include <bits/stdc++.h>
#include <fmt/format.h>
using namespace std;


void swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

void printArr(int arr[], int low, int high) {
  cout << " { ";
  for (int i = low; i < high; i++) {
    cout << arr[i] << (i == high - 1 ? " " : ", ");
  }
  cout << "}\n";
}


int partition(int arr[], int low, int high) {
  int &v = arr[high - 1];

  fmt::print("Partitioning from [{} : {}] where Pivot is '{}': ", low, high, v);
  printArr(arr, low, high);


  int i = low, j = low;
  for (j; j < high; j++) {
    if (arr[j] < v) {
      fmt::print("  INFO: {} < {}. Swapping arr[{}] = '{}' with arr[{}] = {}\n", arr[j], v, j, arr[j], i, arr[i]);
      swap(arr[i], arr[j]);
      cout << "    "; printArr(arr, low, high);
      i++;
    }
  }
  fmt::print("  INFO: Done. Swapping arr[{}] = '{}' with arr[{}] = {}\n", i, arr[i], high, arr[high - 1]);
  swap(arr[i], arr[high - 1]);
  cout << "    "; printArr(arr, low, high);
  fmt::print("  INFO: Pivot Returned: {}\n", i);
  return i;
}

void quicksort(int arr[], int low, int high) {
  if (low < high) {
    fmt::print("\nQuicksort: Low[{}] High[{}]\n", low, high);
    int pivot = partition(arr, low, high);

    quicksort(arr, low, pivot);
    quicksort(arr, pivot + 1, high);
  }
}


int main() {
  int arr[] = {7, 3, 8, 4, 1, 0};
  int array_size = sizeof(arr) / sizeof(int);
  fmt::print("Array size: {}\n", array_size);

  cout << "BEFORE: "; printArr(arr, 0, array_size);
  quicksort(arr, 0, array_size);
  cout << "\nAFTER: "; printArr(arr, 0, array_size);

  return 0;
}