#include "Node.hpp"


/**
 * Binary Search Tree Implementation
 */
class BST {
private:
  Node<int> *root = nullptr;
  friend void preorder(BST&, int);
  friend void postorder(BST&, int);
  friend void inorder(BST&);
  
  /**
   * Internal Recursive Node Value Count
   * @param p Pointer of Root Node to count from
   */
  int _recur_node_val_count(Node<int> *p) {
    // Assign default Node as Root
    if (p == nullptr) {
      return 0;
    }

    // Node Exists
    else {
      // Count current node and all left & rights
      return p->key + _recur_node_val_count(p->left) + _recur_node_val_count(p->right);
    }
  }

  /**
   * Recursively finds the Height of the Tree
   * @param p Poniter to the Node at which to call it's children
   * @param height The current height of that node
   * @returns The Height of that node
   */
  int _recur_get_height(Node<int> *p, int height = 1) {
    if (p) {
      return max(_recur_get_height(p->left, height + 1), _recur_get_height(p->right, height + 1));
    }
    else
      return height - 1;
  }

  /**
   * Utility function for recursively checking if
   *  current Tree is a BST
   * @param p Pointer to the Node of which the Subtree is 
   *  checked for BST Validity
   * @param min Minimum value for Subtree
   * @param max Maximum value for Subtree
   * @returns State of BST
   */
  bool _is_bst_util(Node<int> *p, long min, long max) {
    // Base Case
    if (p == nullptr) 
      return true;
    
    // Constrain Check
    else if (p->key < min || p->key > max)
      return false;
    
    // Recursive Subtree Check
    else
      return _is_bst_util(p->left,  min,                (long)p->key - 1) &&
             _is_bst_util(p->right, (long)p->key + 1,   max);
  }

  /**
   * Search and Find Successor of given Node
   * @param p Pointer to the node to find successor of
   * @returns Pair of Node pointer to the Successor and it's Parent or nullptr if none found
   *  - first = Successor
   *  - second = Parent's Successor
   */
  static pair<Node<int>*, Node<int>*>_get_successor_node(Node<int> *p) {
    // Nullptr!
    if (!p) return { nullptr, nullptr };
  
    // Two Children
    if (p->left && p->right) {
      Node<int> *successor_node = p->right;
      Node<int> *parent_node = nullptr;
      
      while(successor_node->left) {
        parent_node = successor_node;           // Parent
        successor_node = successor_node->left;  // Successor
      }
      return { successor_node, parent_node };
    }
  
    // One Child - Left
    else if (p->left)
      return { p->left, p };
    
    // One Child - Right
    else if (p->right)
      return { p->right, p };
    
    // No Children
    else
      return { nullptr, nullptr };
  }

public:
  BST(){}
  ~BST() { delete_tree(); }

  /**
   * Returns the Successor Node's Value of given  
   *  node
   * @param p Pointer to node to get successor of
   * @returns Value of the Successor Node. -1 if none found
   */
  static int get_successor(Node<int> *p) {
    Node<int> *node = _get_successor_node(p).first;
    if (node)
      return node->key;
    else 
      return -1;
  }

  /**
   * Inserts value into Tree
   * @param value Value to insert into Tree
   */
  void insert(int value) {
    // Search for place to insert Value
    if (root) {
      Node<int> *current = root;

      // Traverse the tree
      while(current) {

        // Go left
        if (value < current->key) {
          if (current->left)
            current = current->left;

          // Left Leaf Insert
          else {
            current->left = new Node<int>(value);
            return;
          }
        }

        // Go Right
        else if (value > current->key) {
          if (current->right)
            current = current->right;

          // Right Leaf Insert
          else {
            current->right = new Node<int>(value);
            return;
          }
        }
        
        // Same Value
        else return;
      }
    }

    // No Root!
    else {
      root = new Node<int>(value);
    }
  }
  
  /**
   * Counts the Values of the nodes in the BST
   */
  int get_node_value_count() {
    if (root)
      return _recur_node_val_count(root);
    else
      return 0;
  }

  /**
   * In Ordered Print: Prints values of Node from Min to Max
   */
  void print_values() {
    inorder(root);
    cout << '\n';
  }

  /**
   * Clears entire Tree
   */
  void delete_tree() {
    delete root;
    root = nullptr;
  }

  /**
   * Removes Node with given Value from Tree
   * @param value Value to remove
   */
  void delete_value(int value) {
    Node<int> *current = root;
    Node<int> *prev = nullptr;
    while(current) {
      // Found Node, remove it!
      if (current->key == value) {
        pair<Node<int> *, Node<int> *> successor_pair = _get_successor_node(current);

        // Move successor to take place
        if (successor_pair.first) {
          // Previous Node Points to Successor
          if (prev) {
            if (prev->right == current)
              prev->right = successor_pair.first;
            else if (prev->left == current) {
              prev->left = successor_pair.first;
            }
          }

          // New Root Node
          else {
            root = successor_pair.first;
          }
          
          // Modify Successor's Parent to point to nothing
          if (successor_pair.second) {
            if (successor_pair.second->left == successor_pair.first)
              successor_pair.second->left = nullptr;
            else if (successor_pair.second->right == successor_pair.first)
              successor_pair.second->right = nullptr;
          }

          // Give current's ownership to Successor
          successor_pair.first->right = current->right;
          successor_pair.first->left = current->left;
        }

        // No successors, remove and update parent
        else if (prev) {
          if (prev->left == current)
            prev->left = nullptr;
          else if (prev->right == current)
            prev->right = nullptr;
        }

        // Root Node Removal
        else {
          delete root;
          root = nullptr;
          break;
        }

        // Clean up & Don't Destruct Children
        current->cleanDecendants = false;
        delete current;
        break;
      }

      else if (value > current->key) {
        prev = current;
        current = current->right;
      }
      else if (value < current->key) {
        prev = current;
        current = current->left;
      }
    }
  }

  /**
   * Searches for the Value in tree
   * @param value The value to search for
   * @returns State of finding the value
   */ 
  bool is_in_tree(int value) {
    Node<int> *node = root;
    while(node) {
      if      (value < node->key)
        node = node->left;
      else if (value > node->key)
        node = node->right;
      else
        return true;
    }
    return false;
  }
  
  /**
   * Returns the height of the Tree
   */
  int get_height() {
    return _recur_get_height(root);
  }

  /**
   * @return Minimum value stored in tree. 0 if tree is empty
   */
  int get_min() {
    if (root == nullptr) return 0;
    
    Node<int> *node = root;
    while (node->left) {
      node = node->left;
    }
    return node->key;
  }

  /**
   * @return Maximum value stored in tree. 0 if tree is empty
   */
  int get_max() {
    if (root == nullptr) return 0;
    
    Node<int> *node = root;
    while (node->right) {
      node = node->right;
    }
    return node->key;
  }
  
  /**
   * @returns State of the Tree being a valid Binary Search Tree
   */
  bool is_bst() {
    return _is_bst_util(root, INT_MIN, INT_MAX);
  }
};

/**
 * Overloaded Postorder print with
 *  access to BST's Private Data
 * @param bst Reference to the BST to print
 * @param indent Indentation after each Child
 */
void postorder(BST &bst, int indent = 0) {
  postorder(bst.root, indent);
}

/**
 * Overloaded Preorder print with
 *  access to BST's Private Data
 * @param bst Reference to the BST to print
 * @param indent Indentation after each Child
 */
void preorder(BST &bst, int indent = 0) {
  preorder(bst.root, indent);
}

/**
 * Overloaded Inorder print with
 *  access to BST's Private Data
 * @param bst Reference to the BST to print
 */
void inorder(BST &bst) {
  preorder(bst.root);
}



// Testing Macros
#define TEST(name) cout << "== TEST: " << name << " ==\n";

int main() {
  BST bst;

  // TEST:
  TEST("Root Removal")
  cout << "Adding 25...\n";
  bst.insert(25);
  preorder(bst);

  cout << "\nRemoving 25...\n";
  bst.delete_value(25);
  preorder(bst);

  // TEST:
  TEST("Known Tree Insertion")
  cout << "Constructing BST...\n";
  bst.insert(25);
  bst.insert(20);
  bst.insert(36);
  bst.insert(10);
  bst.insert(22);
  bst.insert(5);
  bst.insert(12);
  bst.insert(30);
  bst.insert(28);
  bst.insert(40);
  bst.insert(38);
  bst.insert(48);
  preorder(bst);

  vector<int> arr = { 36, 40, 48, 25, 30 };
  for (const int value_to_remove : arr) {
    cout << "\nRemoving '" << value_to_remove << "'...\n";
    bst.delete_value(value_to_remove);
    preorder(bst);
  }

  bst.insert(30);
  cout << "\nAdding 30...\n";
  preorder(bst);

  cout << "\nClearing BST...\n";
  bst.delete_tree();
  preorder(bst);
  cout << '\n';
  
  // TEST:
  TEST("Random Tree")
  srand(time(nullptr));
  for (int i=0; i<10; i++) {
    long value = rand() % 100;
    cout << "Inserting: " << value << '\n';;
    bst.insert(value);
  }
  preorder(bst);
  cout << "Node Count: " << bst.get_node_value_count() << '\n';
  bst.print_values();
  
  // Stats
  cout << "\n== Stats ==\n";
  cout << "is_in_tree(4)? " << boolalpha << bst.is_in_tree(4) << '\n';
  cout << "Tree Height = " << bst.get_height() << '\n';
  cout << "Minimum Value = " << bst.get_min() << '\n';
  cout << "Maximum Value = " << bst.get_max() << '\n';
  cout << "Is BST? " << boolalpha << bst.is_bst() << '\n';
  return 0;
}