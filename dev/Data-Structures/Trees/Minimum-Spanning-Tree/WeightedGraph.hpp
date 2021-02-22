#include <list>
#include <vector>
#include <fmt/format-inl.h>

template< typename T >
struct Edge;

template< typename T >
struct Vertex {
  const int _id;
  T data;
  std::list<Edge<T>> edges;

  Vertex(int id): _id(id), edges({}) {}
};

// Vertex -> Vertex Traversal
template< typename T >
struct Edge {
  Vertex<T>  *v;
  int     weight;
};


class WeightedGraph {
private:
  std::vector<Vertex<int>> graph;

public:
  WeightedGraph(std::initializer_list<std::initializer_list<int>> args) {

    // Instantiation Pass
    unsigned int id = 0;
    for (auto vertex : args) {
      // Create the Vertex
      Vertex<int> v(id++);
      v.data = *vertex.begin();
      graph.push_back(v);
    }

    // Association Pass
    id = 0;
    for (auto vertex : args) {
      for (auto it = vertex.begin() + 1; it != vertex.end(); it += 2) {
        // Link each Vertex
        graph[id].edges.push_back({
          &graph[*it],    // Vertex Address
          *(it+1)         // Weight with Traversing to Vertex
        });
      }
      id++;
    }

  }

  void printGraph() {
    fmt::print("== Constructed Graph ==\n");
    for (auto vertex : graph) {
      for (auto edge : vertex.edges)
        fmt::print("{} -({})-> {}\n", vertex.data, edge.weight, edge.v->data);
      fmt::print("\n");
    }
  }

  /**
   * @return A copy of the internal graph
   */
  std::vector<Vertex<int>> getGraph() {
    return graph;
  }
};

