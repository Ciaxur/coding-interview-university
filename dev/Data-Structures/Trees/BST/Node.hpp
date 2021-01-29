#include <bits/stdc++.h>
using namespace std;

/**
 * Node Class that handles keeping track
 *  of Left and Right Linked Nodes with any
 *  types
 */
template< typename T >
struct Node {
  Node *left, *right;
  T key;

  // State of Cleaning Child Nodes on Destruction
  bool cleanDecendants = true;

  Node(T val = 0, Node *l = nullptr, Node *r = nullptr) : left(l), right(r), key(val) {
#ifdef DEBUG
    cout << "Node Creation...\n";
    cout << " - Key: " << key << '\n';
    cout << " - Left: " << left << '\n';
    cout << " - Right: " << right << '\n';
#endif
  };

  ~Node() {
#ifdef DEBUG
    cout << "Freeing up Node Space\n";
    cout << " - Key: " << key << '\n';
    cout << " - Left: " << left << '\n';
    cout << " - Right: " << right << '\n';
#endif
    if (cleanDecendants) {
      if(left) delete left;
      if(right) delete right;
    }
  }
};


/**
 * Overloaded Output Stream for Node Types
 */
template< typename T >
ostream &operator<<(ostream &out, const Node<T>& rhs) {
  if (rhs.left) out << rhs.left->key;
  else out << "null";
  
  if (rhs.right) out << ", " << rhs.right->key;
  else out << ", null";
  
  return out;
}

/**
 * Prints Node in an Array Structure 
 */
template< typename T >
void printNode( Node<T> &node ) {
  cout << "{ ";
  if (node.left) {
    cout << " ";
    printNode(*node.left);
  }
  if (node.right) {
    printNode(*node.right);
    cout << " ";
  }
  cout << node;
  cout << " }";
}


template< typename T >
void postorder(Node<T> *p, int indent = 0) {
  if (p != nullptr) {
    if (p->left)
      postorder(p->left, indent + 4);
    if (p->right)
      postorder(p->right, indent + 4);
    if (indent)
      cout << setw(indent) << ' ';
    cout << p->key << '\n';
  }
}

template < typename T >
void preorder(Node<T> *p, int indent = 0) {
  if (p != nullptr) {
    if (indent)
      cout << setw(indent) << ' ';

    cout << p->key << '\n';

    if (p->left)
      preorder(p->left, indent + 4);
    if (p->right)
      preorder(p->right, indent + 4);
  }
}

template < typename T >
void inorder(Node<T> *p) {
  if (p != nullptr) {
    if (p->left)
      inorder(p->left);
    cout << p->key << ' ';
    if (p->right)
      inorder(p->right);
  }
}
