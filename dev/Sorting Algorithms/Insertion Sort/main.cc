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


void insertion_sort(int arr[], int lo, int hi) {
  for (int i = lo; i < hi; i++) {
    int k = i;    // Assume i is Lowest

    while( k > 0 && arr[k-1] > arr[k]) {
      fmt::print("  Swapping {} with {}\n", arr[k-1], arr[k]);
      swap(arr[k-1], arr[k]);
      fmt::print("  "); printArr(arr, lo, hi);
      k--;
    }
  }
}


int main() {
  int arr[] = {7, 8, 3, 4, 9, 1};
  int arr_size = sizeof(arr) / sizeof(int);

  fmt::print("BEFORE: "); printArr(arr, 0, arr_size); fmt::print("\n");
  insertion_sort(arr, 0, arr_size);
  fmt::print("\nAFTER: "); printArr(arr, 0, arr_size);
  
  

  return 0;
}