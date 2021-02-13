#include <list>
#include <vector>
#include <fmt/format.h>
using namespace std;

template< typename T >
struct Vertex {
  // Member Variables
  const int       _id;
  bool            visited;
  int             weight;       // Traversal Weight
  T               data;
  std::list<int>  edges;        // Indicies of other Verticies

  // Constructors
  Vertex(int id) : visited(false), weight(1), edges({}), _id(id) {}

  // Compare Overloads
  bool operator> (const Vertex<T>& rhs){ return this->weight > rhs.weight; }
  bool operator< (const Vertex<T>& rhs){ return this->weight < rhs.weight; }
  bool operator<=(const Vertex<T>& rhs){ return !(this->weight > rhs.weight); }
  bool operator>=(const Vertex<T>& rhs){ return !(this->weight < rhs.weight); }
  bool operator!=(const Vertex<T>& rhs){ return !(this->weight == rhs.weight); }
  bool operator==(const Vertex<T>& rhs){ return this->weight == rhs.weight; }
};


/**
 * Creates a Graph given a list of Verticies and their
 *  edges
 * @param args { vertex: { edges } }. Example { {1,2}, {2}, {} }
 * @returns Connected Graph (List of Verticies)
 */
vector<Vertex<int>> createGraph(initializer_list<initializer_list<int>> args) {
  // Construct the entire Graph
  vector<Vertex<int>> graph;
  
  unsigned int id = 0;
  for (auto vertex : args) {
    // Create the Vertex
    Vertex<int> v(id++);

    // Link Vertex to Edges
    for (auto edge : vertex)
      v.edges.push_back(edge);
    
    // Add the Vertex to the Graph
    graph.push_back(v);
  }

  return graph;
}

/**
 * Resets 'visited' in all verticies in the given graph
 * @param graph Graph to reset verticies of
 */
void resetGraphDiscovery(vector<Vertex<int>> &graph) {
  for (auto &v : graph) {
    v.visited = false;
    v.weight = 1;
  }
}

// Simply prints the graph and it's edges
void printGraph(vector<Vertex<int>> &graph) {
  fmt::print("== Constructed Graph ==\n");
  for (auto vertex : graph) {
    fmt::print("Vertex[{}] Weight({}) = ", vertex._id, vertex.weight);
    for (auto edge : vertex.edges)
      fmt::print("{} ", edge);
    fmt::print("\n");
  }
}
