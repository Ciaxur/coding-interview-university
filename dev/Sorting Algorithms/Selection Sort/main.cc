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


void selection_sort(int arr[], int low, int hi) {
  for (int i=low; i<hi; i++) {
    int least = i;   // Assume i is lowest value

    for (int j = i + 1; j < hi; j++) {
      if (arr[j] < arr[least]) {
        fmt::print("{} < {}: TRUE\n", arr[j], arr[least]);
        least = j;
      }
    }

    fmt::print("Swapping {} with {}\n\t", arr[i], arr[least]);
    swap(arr[i], arr[least]);
    printArr(arr, low, hi);
  }
}

int main() {
  int arr[] = {7, 3, 8, 4, 1, 0};
  int array_size = sizeof(arr) / sizeof(int);

  fmt::print("BEFORE: ");
  printArr(arr, 0, array_size);
  fmt::print("\n");

  selection_sort(arr, 0, array_size);

  fmt::print("\nAFTER:  ");
  printArr(arr, 0, array_size);

  return 0;
}