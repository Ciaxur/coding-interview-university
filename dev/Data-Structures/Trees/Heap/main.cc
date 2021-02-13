#include "Heap.hpp"

int main() {
  Heap<> h({7, 3, 4, 9, 1, 2});

  cout << "BEFORE:\n";
  print(h.get_array());
  int max = h.extract_max();

  cout << "AFTER:\n";
  print(h.get_array());
  cout << "...Extracted: " << max << '\n';

  cout << "\nInserting '" << max << "'...\n";
  h.insert(max);
  print(h.get_array());


  // TEST: Debug prints with Sort
  // Heap::heap_sort(arr, Heap::HeapType::MAX, true);

  return 0;
}