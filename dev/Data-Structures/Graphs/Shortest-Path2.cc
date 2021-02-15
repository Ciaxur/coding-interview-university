/**
 * Shortest Path implemented with C++'s STL heap methods
 *  from the Algorithm Library
 */

#include <unordered_map>
#include "Vertex.hpp"
#include <algorithm>
#include <queue>
using namespace std;


struct VertexMeta {
  Vertex<int> *vertex;    // Vertex Itself
  Vertex<int> *prev;      // Vertex's Predecesor
  int          dist;      // Distance to Vertex from Source
  bool         isTracked; // State of Tracking Vector

  VertexMeta(Vertex<int> *_v, Vertex<int> *_p, int d)
    : vertex(_v), prev(_p), dist(d), isTracked(true) {};
  VertexMeta() {}
};

unordered_map<int, VertexMeta> dijkstra(vector<Vertex<int>> &graph, Vertex<int> *source, bool debugPrints = false) {
  // Data Tracking Containers
  unordered_map<int, VertexMeta> vertData;
  auto indexInVector = [](vector<int> &v, int i) {
    for (const int &elt : v)
      if (elt == i) return true;
    return false;
  };

  // Comparitor and Heap
  auto cmp = [&](const int &left, const int &right) {
    return vertData.at(left).dist > vertData.at(right).dist;
  };
  vector<int> Q;
  
  
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
    Q.push_back(v._id);
    push_heap(Q.begin(), Q.end(), cmp);
  }

  // Init source's Distance
  vertData.at(source->_id).dist = 0;

  // Start the algo!
  while (!Q.empty()) {
    // Best Vertex
    auto vmeta = vertData.at(Q.front());
    pop_heap(Q.begin(), Q.end(), cmp);
    Q.pop_back();

    // Check neighbors that are also in Q
    for (const int &neighborID: vmeta.vertex->edges) {
      if (indexInVector(Q, neighborID)) {
        // Calculate the Score of taking the path of the Node
        int score = vmeta.dist + vertData.at(neighborID).vertex->weight;
        if (debugPrints) {
          fmt::print("{} to {} new score of '{}'\n", vmeta.vertex->_id, neighborID, score);
          fmt::print(" score = {} | u.dist = {}'\n", score, vertData.at(neighborID).dist);
        }

        if (score < vertData.at(neighborID).dist) {
          vertData[neighborID].dist = score;
          vertData[neighborID].prev = vmeta.vertex;

          if(debugPrints) fmt::print("  Added {} with score of {}\n", neighborID, score);
          Q.push_back(neighborID);
          push_heap(Q.begin(), Q.end(), cmp);
        }
      }
    }
  }

  // Return Collected Data
  return vertData;
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

  auto vertData = dijkstra(graph, &graph[0]);
  
  // Output Result
  fmt::print("\n=== RESULT ===\n");
  Vertex<int> *v = vertData.at(graph.back()._id).vertex;
  queue<int> Q;
  while(v) {
    Q.push(v->_id);

    fmt::print("{} ", v->_id);
    v = vertData.at(v->_id).prev;
    if (v)
      fmt::print("-> ");
  }
  
  fmt::print("\n\n=== DISTANCE ===\n");
  while(!Q.empty()) {
    fmt::print("{} ", vertData.at(Q.front()).dist);
    Q.pop();
    if (!Q.empty())
      fmt::print("-> ");
  }
  fmt::print("\n\nDONE :)");

  return 0;
}