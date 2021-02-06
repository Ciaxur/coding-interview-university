#include <Data-Structures/Trees/Heap/Heap.hpp>



vector<int> HeapSort(vector<int> array) {
  fmt::print("Constructing Array: "); print(array);
  Heap h(array);
  fmt::print("Heap Sort = ");
  print_array(h.get_array(), 0, h.get_size());


  // Construct Resulting Array
  vector<int> sorted(array.size(), 0);
  
  fmt::print("Extracting Max Heap, building Sorted Array...\n");
  int k = h.get_size();
  while(k > 0 || !h.is_empty()) {
    int extracted_value = h.extract_max();
    fmt::print("Extracted: {}\n  ", extracted_value);
    print_array(h.get_array(), 0, h.get_size());
    sorted[--k] = extracted_value;
  }

  return sorted;
}


int main() {
  vector<int> res = HeapSort({2, 6, 7, 8, 3, 6});
  fmt::print("Done Sorting\n  ");
  print(res);
}