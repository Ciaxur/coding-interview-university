/**
 * Undirected Graph ADT
 */
#include "Vertex.hpp"
#include <stack>
#include <queue>
#include <fmt/format.h>
using namespace std;


// Search Algorithms
namespace Search {
/**
 * Recursive DFS
 * @param graph The entire graph reference
 * @param v Current Vertex
 * @param findID Vertex ID to find
 * @return Vertex with given ID
 */
Vertex<int> *DFS_recur(vector<Vertex<int>> &graph, Vertex<int> *v, int findID) {
  v->visited = true; // Discovered
  fmt::print("Discovering 'v{}'\n", v->_id);
  if (v->_id == findID) {
    return v;
  }

  // Discover Adjacent Verticies
  for (int directV_index : v->edges) {
    auto directV = &graph[directV_index];
    if (!directV->visited)
      return DFS_recur(graph, directV, findID);
    else
      fmt::print("  Already Discovered 'v{}'\n", directV->_id);
  }
  return nullptr;
}

/**
 * Iterative DFS using a Stack to keep track of Verticies
 */
Vertex<int> *DFS_iter(vector<Vertex<int>> &graph, Vertex<int> *v, int findID) {
  stack<Vertex<int> *> S;
  S.push(v);

  while (!S.empty()) {
    v = S.top();
    S.pop();

    fmt::print("Discovering 'v{}'\n", v->_id);
    if (!v->visited) {
      v->visited = true;
      if (v->_id == findID) {
        return v;
      }

      // LIFO add to stack
      for (int adjIndex : v->edges)
        S.push(&graph[adjIndex]);
    } else
      fmt::print("  Already Discovered 'v{}'\n", v->_id);
  }
  return nullptr;
}

/**
 * Iterative BFS implementation of Graph
 * @param graph Entire Graph with Verticies
 * @param v Root Vertex
 * @param findID Vertex ID to find
 * @return Vertex with given ID
 */
Vertex<int> *BFS(vector<Vertex<int>> &graph, Vertex<int> *v, int findID) {
  queue<Vertex<int> *> Q;
  v->visited = true;
  Q.push(v);

  while (!Q.empty()) {
    v = Q.front();
    Q.pop();

    for (int adjIndex : v->edges) {
      if (!graph[adjIndex].visited) {
        fmt::print("Discovering 'v{}'\n", graph[adjIndex]._id);
        graph[adjIndex].visited = true;

        if (v->_id == findID) {
          return v;
        }

        Q.push(&graph[adjIndex]);
      }
    }
  }

  return nullptr;
}
} // namespace Search


int main() {
  // DFS & BFS Test
  auto graph = createGraph({
    {1, 2},
    {0, 3},
    {0, 5},
    {1, 4},
    {3, 5},
    {2, 4}
  });

  printGraph(graph);
  
  int findId = 3;
  fmt::print("\n== Iterative DFS: Find 'v{}' ==\n", findId);
  auto res = Search::DFS_iter(graph, &graph[0], findId);
  fmt::print("Found: v{}\n", res->_id);

  fmt::print("\n== Recursive DFS: Find 'v{}' ==\n", findId);
  resetGraphDiscovery(graph);
  res = Search::DFS_recur(graph, &graph[0], findId);
  fmt::print("Found: v{}\n", res->_id);

  fmt::print("\n== BFS: Find 'v{}' ==\n", findId);
  resetGraphDiscovery(graph);
  res = Search::BFS(graph, &graph[0], findId);
  fmt::print("Found : v{}\n", res->_id);
  
  return 0;
}