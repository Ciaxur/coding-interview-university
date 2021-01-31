#include <bits/stdc++.h>
#include <fmt/format.h>
using namespace std;


// Swaps values of a and b
void swap (int &a, int &b) { 
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

// Prints Given Vector
void print(vector<int> &vec) {
  cout << "{ ";
  for (const int &elt : vec)
    cout << elt << (elt == vec[vec.size() - 1] ? "" : ", ");
  cout << " }\n";
}


// Implementation of Max-Heap & Min-Heap
class Heap {
private:
  vector<int> data;

public:
  enum HeapType { MIN, MAX };
  Heap(vector<int> arr): data(arr) {
    heap_sort(data);
  };

  /**
   * Returns the Number of elements stored
   */
  const int get_size() {
    return data.size();
  }

  /**
   * Returns the Empty state of Heap
   */
  bool is_empty() {
    return data.empty();
  }
  
  /**
   * Returns Max item without Removing it
   */
  int get_max() {
    return data[0];
  }

  /**
   * Returns Max value, removing the node
   *  afterwards
   */
  int extract_max() {
    int maxVal = get_max();
    remove(0);
    return maxVal;
  }

  /**
   * Sifts Top node down
   */
  void sift_down() {
    heapify(data);
  }

  /**
   * Builds heap from bottom up
   */
  void sift_up() {
    for (int i = data.size() - 1; i > 0; i--) {
      int parent = (i - ((i + 1) % 2)) / 2;

      if (data[parent] < data[i])
        swap(data[parent], data[i]);
    }
  }

  /**
   * Inserts given Value to Heap
   * @param value Value to insert into Heap
   */
  void insert(int val) {
    data.push_back(val);
    sift_up();
  }

  /**
   * Removes node at Index
   * @param index Node to remove
   */
  void remove(int index) {
    // Exchange Index Value with Leaf node end
    data[index] = data[data.size() - 1];
    data.pop_back();

    // Heapify from Index
    heapify(data, index);
  }


  /**
   * Returns stored Array of Data
   */
  vector<int> &get_array() {
    return data;
  }

  /**
   * Heapifies given Array
   * @param arr Array to Heapify
   */
  static void heapify(vector<int> &arr, int i = 0) {
    // Base Case
    int j = arr.size() - 1;
    if (i >= j-1) return;

    // Bubble Down until Sorted
    // Compare Children
    int left = (2 * (i + 1)) - 1;
    int right = 2 * (i + 1);

    // One Child
    if (right > j) {
      if (arr[left] > arr[i]) {
        swap(arr[left], arr[i]);
        Heap::heapify(arr, left);
      }
    }
    
    else if ((arr[left] > arr[right]) && arr[left] > arr[i]) {
      swap(arr[left], arr[i]);
      Heap::heapify(arr, left);
    }

    else if ((arr[right] > arr[left]) && arr[right] > arr[i]) {
      swap(arr[right], arr[i]);
      Heap::heapify(arr, right);
    }
  }

  /**
   * Takes an unsorted array and turns it into
   *  a storted array using Max-Heap
   * @param arr Unsorted array to sort
   * @param type Max or Min Heap
   */
  static void heap_sort(vector<int> &arr, Heap::HeapType type = MAX, bool debugPrints = false) {
    // Bubble end elt to Max
    for (int j = arr.size() - 1; j > 0; j--) {
      if (debugPrints) {
        cout << "\nRound[" << j << "]: \n"
             << " Swap " << arr[0] << " & " << arr[j] << '\n';
      }
             
      swap(arr[0], arr[j]);
      Heap::heapify(arr);

      if (debugPrints) {
        cout << "  ";
        print(arr);
      }
    }
  }
};



int main() {
  Heap h({7, 3, 4, 9, 1, 2});

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