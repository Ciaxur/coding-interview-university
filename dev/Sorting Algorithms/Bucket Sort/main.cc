#include <bits/stdc++.h>
#include <fmt/format.h>
using namespace std;

void printArr(int arr[], int size) {
  cout << " { ";
  for (int i = 0; i < size; i++) {
    cout << arr[i] << (i == size - 1 ? " " : ", ");
  }
  cout << "}\n";
}

void printArr(vector<int> arr, int size) {
  cout << " { ";
  for (int i = 0; i < size; i++) {
    cout << arr[i] << (i == size - 1 ? " " : ", ");
  }
  cout << "}\n";
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

/**
 * General Bucket sort given Array with Range
 *  and bucket number
 * @param arr Array to Sort
 * @param lo Low Array Index
 * @param hi High Array Index
 * @param max_key Highest Key Value
 * @param k Number of Buckets
 */
void bucket_sort(int arr[], int lo, int hi, int max_key, int k = 5) {
  // Create Buckets
  vector<int> buckets[k];

  // Fill Buckets
  fmt::print("\nFilling Buckets...\n");
  for (int i = lo; i < hi; i++) {
    int b_index = floor((k - 1) * arr[i] / max_key);
    fmt::print("  Inserting '{}' at bucket[{}]\n", arr[i], b_index);

    // Insert Value into Bucket Index's Tail
    buckets[b_index].push_back(arr[i]);
  }

  // Sort Each Bucket (Selection Sort)
  fmt::print("\nSorting Each Bucket...\n");
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < buckets[i].size(); j++) {
      int k = j;    // Assume j'th Index is Least
      for (int x = j; x < buckets[i].size(); x++) {
        if (buckets[i][x] < buckets[i][k])
          k = x;    // New Smallest Value
      }
      swap(buckets[i][k], buckets[i][j]);
    }
  }

  // Print Buckets
  for (int i = 0; i < k; i++) {
    fmt::print("Bucket[{}]\n", i);
    printArr(buckets[i], buckets[i].size());
  }

  // Merge Buckets into Given Array
  int arr_i = lo;
  for (auto bucket : buckets)
    for(auto elt : bucket)
      arr[arr_i++] = elt;
}

int main() {
  int arr[] = {7, 12, 11, 32, 3, 6, 28, 0, 2, 5};
  int arr_size = sizeof(arr) / sizeof(int);


  fmt::print("Sorting: "); printArr(arr, arr_size);
  bucket_sort(arr, 0, arr_size, 32, 5);
  fmt::print("\nResult: "); printArr(arr, arr_size);

  return 0;
}