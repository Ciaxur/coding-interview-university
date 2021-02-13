#include <unordered_map>
#include "Vertex.hpp"
#include "Trees/Heap/Heap.hpp"

struct VertexMeta {
  Vertex<int> *vertex;    // Vertex Itself
  Vertex<int> *prev;      // Vertex's Predecesor
  int          dist;      // Distance to Vertex from Source
  bool         isTracked; // State of Tracking Vector

  VertexMeta(Vertex<int> *_v, Vertex<int> *_p, int d)
    : vertex(_v), prev(_p), dist(d), isTracked(true) {};
  VertexMeta() {}
};

namespace MinHeap {
  
void swap (int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void heapify(vector<int> &arr, unordered_map<int, VertexMeta> &meta, int i = 0) {
  // Base Case
  int j = arr.size() - 1;
  if (i >= j - 1)
    return;

  // Bubble Down until Sorted
  // Compare Children
  int left = (2 * (i + 1)) - 1;
  int right = 2 * (i + 1);

  // One Child
  if (right > j) {
    if (meta.at(arr[left]).dist > meta.at(arr[i]).dist) {
      MinHeap::swap(arr[left], arr[i]);
      heapify(arr, meta, left);
    }
  }

  else if ((meta.at(arr[left]).dist > meta.at(arr[right]).dist) && meta.at(arr[left]).dist > meta.at(arr[i]).dist) {
    MinHeap::swap(arr[left], arr[i]);
    heapify(arr, meta, left);
  }

  else if ((meta.at(arr[right]).dist > meta.at(arr[left]).dist) && meta.at(arr[right]).dist > meta.at(arr[i]).dist) {
    MinHeap::swap(arr[right], arr[i]);
    heapify(arr, meta, right);
  }
}

void heap_sort(vector<int> &arr, unordered_map<int, VertexMeta> &meta) {
  for (int j = arr.size() - 1; j > 0; j--) {
    MinHeap::swap(arr[0], arr[j]);
    MinHeap::heapify(arr, meta);
  }
}

}; // namespace MinHeap



void dijkstra(vector<Vertex<int>> &graph, Vertex<int> *source) {
  // Data Tracking Containers
  unordered_map<int, VertexMeta> vertData;

  // Construct Min-Heap with Comparator
  auto cmp = [&](const int &left, const int &right) {
    return vertData.at(left).dist < vertData.at(right).dist;
  };
  Heap<decltype(cmp)> Q(cmp);
  
  // Construct the Map, setting discovery data
  for (Vertex<int> &v : graph) {
    vertData.insert({
      v._id,
      {
        &v, 
        nullptr,                        // No Predecesor
        numeric_limits<int>::max()      // Unknown Distance from Source
      }
    });

    // Add to Queue
    Q.insert(v._id);
  }

  // Initialize Source's initial Distance
  vertData.at(source->_id).dist = 0;
  
  // Start the Algo!
  while (!Q.is_empty()) {
    // Best Vertex
    auto vmeta = vertData[Q.extract_max()];
    fmt::print("Extracted v{} with distance {}\n", vmeta.vertex->_id, vmeta.dist);

    // Check neighbors thar are still in Q
    for (const int &neighborID : vmeta.vertex->edges) {
      // Only ones that are in Q
      if (Q.get_array())

    }
    
  }
}

int main() {
  // Dijkstra Test
  auto graph = createGraph({
    {2},
    {3,4},
    {0,3},
    {1,2,7},
    {1,7,9},
    {10,6},     // 5
    {5,10,11,7},
    {3,4,8,6,11},
    {7,9},
    {4,8,12,13,14},
    {5,6},      // 10
    {6,7,15,16},
    {9,16},
    {9,16},
    {9},
    {11},       // 15
    {11,12,13,17,19},
    {16,21,24},
    {22},
    {16,20},
    {19,22,21}, // 20
    {17,20,23},
    {18,20,25,26},
    {21,26},
    {17,26},
    {22},       //25
    {22,23,24}
  });

  // printGraph(graph);
  dijkstra(graph, &graph[0]);

  return 0;
}