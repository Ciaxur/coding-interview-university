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

/**
 * Runs Dijkstra's algorithm in search of the end node (target) in the
 *  given graph, returning a map of collected graph data.
 * Target is implicitly given as the graph's last node
 * @param graph Reference to the overall graph
 * @param source Pointer to the source vertex
 * @param debugPrints (Optional) Flag to output debug prints
 * @return Map of collected map data
 */
unordered_map<int, VertexMeta> dijkstra(vector<Vertex<int>> &graph, Vertex<int> *source, bool debugPrints = false) {
  // Data Tracking Containers
  unordered_map<int, VertexMeta> vertData;
  auto indexInVector = [](vector<int> &v, int i) {
    for (const int &elt : v)
      if (elt == i) return true;
    return false;
  };
  

  // Construct Min-Heap with Comparator
  auto cmp = [&](const int &left, const int &right) {
    return vertData.at(left).dist > vertData.at(right).dist;
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
    auto vmeta = vertData.at(Q.extract_max());

    // Check neighbors thar are still in Q
    for (const int &neighborID : vmeta.vertex->edges) {
      // Only ones that are in Q
      if (vmeta.dist != numeric_limits<int>::max()) {
        if (indexInVector(Q.get_array(), neighborID)) {
          // Calculate the Score of taking the path of the Node
          int score = vmeta.dist + vertData.at(neighborID).vertex->weight;
          if (debugPrints) {
            fmt::print("{} to {} new score of '{}'\n", vmeta.vertex->_id, neighborID, score);
            fmt::print(" score = {} | u.dist = {}'\n", score, vertData.at(neighborID).dist);
          }

          if (score < vertData.at(neighborID).dist) {
            vertData[neighborID].dist = score;
            vertData[neighborID].prev = vmeta.vertex;

            if (debugPrints) fmt::print("  Added {} with score of {}\n", neighborID, score);
            Q.insert(neighborID);
          }
        }
      }
    }
  }

  // Return collected data
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

  // printGraph(graph);
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