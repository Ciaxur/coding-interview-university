#include <bits/stdc++.h>
#include "WeightedGraph.hpp"
using namespace std;


// Holds Vertex Metadata used for
//   creating a Minimum Spanning Tree
struct VertexMeta {
  Vertex<int> *node;
  VertexMeta *parent;
  int value;
};


/* 
  Find
    - With each find, take the nodes (all of them being traversed upward)
      and set parent to the Root (better finds later) making the tree "bushy"
    - This is called Path Compression
*/
VertexMeta* findParent(VertexMeta &vertex) {
  // TODO: Path Compression

  // Find Parent
  VertexMeta *ptr = vertex.parent;
  while(ptr->parent)
    ptr = ptr->parent;
  return ptr;
}





int main() {
  // Create Connected Weighted Graph
  WeightedGraph g({
    { // v1
      1,        // Vertex Value 1
      2, 1,     // Connected to vertex 2 with Weight 1
      9, 4,     // Connected to vertex 9 with Weight 4
      3, 3      // Connected to vertex 3 with Weight 3
    },
    { // v2
      2,
      1, 1,
      3, 2,
      4, 1
    },
    { // v3
      3,
      1, 3,
      2, 2,
      8, 3,
      7, 2,
      4, 2
    },
    { // v4
      4,
      2, 1,
      3, 2,
      7, 3,
      6, 3,
      5, 5
    },
    { // v5
      5,
      4, 5,
      6, 4,
      12, 2
    },
    { // v6
      6,
      5, 4,
      4, 3,
      7, 6,
      11, 1
    },
    { // v7
      7,
      6, 6,
      4, 3,
      3, 2,
      8, 2,
      11, 4
    },
    { // v8
      8,
      7, 2,
      3, 3,
      9, 4,
      10, 2
    },
    { // v9
      9,
      1, 4,
      8, 4,
      10, 5
    },
    { // v10
      10,
      9, 5,
      8, 2,
      11, 3
    },
    { // v11
      11,
      10, 3,
      7, 4,
      6, 1,
      12, 4
    },
    { // v12
      12,
      11, 4,
      5, 2
    }
  });
  
  /* Initialization
    - Heap where value is least (Front) 
      - Insert all Nodes
      - Remove from heap as you connect
    - Each Node's Data Structure:
      - parent = null
      - value = INFINITY
  */
  auto g_copy = g.getGraph();
  auto cmp = [](const VertexMeta &left, const VertexMeta &right) { return left.value > right.value; };
  
  vector<VertexMeta> graphHeap;
  for (auto &elt : g_copy)
    graphHeap.push_back({ &elt, nullptr, numeric_limits<int>::max() });
  

  /*
    Union-Find, unionizing Sets NOT in the same set (Prevents Cycles)
    
      - NOTE: Using Kruskel's Algo
        - Kruskel -> Any node in the tree
      - By using Parent Pointers in an Array where the Root is the Set
      - Union the smallest tree with the bigger (Hight >)
      - When unionizing, point to the root of the set
  */

  
  // Get high priority from Heap
  // Being Union Find
  VertexMeta &v = graphHeap.front();
  DFS_MST(v, graphHeap);
  


    

  return 0;
}
