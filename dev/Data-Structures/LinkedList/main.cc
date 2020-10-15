#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
  // Simple Constructor
  Node(Node<T> *p, Node<T> *n, T d) : prev(p), next(n), data(d) {}

  // Node Data
  Node *prev;
  Node *next;
  T data;
};

template< typename T >
class LinkedList {
  private:
    Node<T> *head;
    Node<T> *tail;
    size_t _size;

    // Can't Perform on No Data; Throw Exception
    void _checkValidSize() {
      if (_size == 0) {
        throw std::length_error("No Data in List");
      }
    }

    // Out of Bounds Test; Throw Exception
    void _checkOutOfBounds(size_t index) {
      if (index < 0 || index >= _size) {
        throw std::out_of_range("Index out of bounds");
      }
    }

    /**
     * Returns index of node at index
     * @param index Index to search for 
     * @param fromTail Optional Parameter to start at tail
     */
    Node<T>* _getNodeAt(size_t index, bool fromTail = false) {
      Node<T> *curr = fromTail ? tail : head;
      for (size_t i = 0; i < index; i++) {
        curr = fromTail ? curr->prev : curr->next;
      }
      return curr;
    }

  public:
    LinkedList() {
      _size = 0;
      head = nullptr,
      tail = nullptr;
    }

    // Clean up Data
    ~LinkedList() {
      Node<T> *curr = head;
      while(curr != nullptr) {
        Node<T> *next = curr->next;
        delete curr;
        curr = next;
      }
    }
  

  // Returns number of Data Elements
  const size_t size() {
    return _size;
  }

  // Returns if List is Empty
  const bool empty() {
    return _size == 0;
  }

  /**
   * Add value to the tail of the List
   * @param value Value to be added
   */
  void push_back(T value) {
    Node<T> *node = new Node<T>(tail, nullptr, value);

    // Fist Element?
    if (head == nullptr) {
      head = node;
    } else {
      tail->next = node;
    }

    // New Data
    tail = node;
    _size++;
  }

  /**
   * Adds item to front of the List
   * @param value The value to place in the List
   */
  void push_front(T value) {
    // Create Data
    Node<T> *node = new Node<T>(nullptr, head, value);

    // Add to List
    if (head == nullptr) {  // New Head?
      tail = node;
    } else {
      head->prev = node;
    }

    head = node;
    _size++;
  }

  /**
   * Removes element at the end and returns
   *  that value
   * @returns Tail Element 
   */
  T pop_back() {
    // Check Valid Data
    _checkValidSize();

    // Store Data to Return
    T value = tail->data;

    // Free up and assign new Tail
    if (tail != head) {
      Node<T> *newTail = tail->prev;
      newTail->next = nullptr;
      delete tail;
      tail = newTail;
    } else {
      delete tail;
      tail = head = nullptr;
    }

    _size--;
    return value;
  }

  /**
   * Removes the Front Element, return it's value
   * @returns Value of Removed Element
   */
  T pop_front() {
    // Verify Procedure can be done
    _checkValidSize();

    // Store Data being removed
    T data = head->data;

    // Assign new Head
    if (head != tail) {
      Node<T> *newHead = head->next;
      newHead->prev = nullptr;
      delete head;
      head = newHead;
    } else {  // No Head at all
      delete head;
      tail = head = nullptr;
    }

    _size--;
    return data;
  }

  /**
   * @returns the data of the first Element 
   */
  const T front() {
    _checkValidSize();
    return head->data;
  }

  /**
   * @returns the data of the last Element 
   */
  const T back() {
    _checkValidSize();
    return tail->data;
  }

  /**
   * Obtains value at given Index
   * @param index The Index to Obtain
   * @returns Value at given Index
   */
  T value_at(size_t index) {
    // Initial Validation
    _checkValidSize();
    _checkOutOfBounds(index);

    Node<T> *curr = _getNodeAt(index);
    return curr->data;
  }

  /**
   * Obtain value at index from tail
   * @param n Index starting from tail
   */
  T value_n_from_end(size_t n) {
    return _getNodeAt(n, true)->data;
  }

  /**
   * Inserts Item at given Index
   * @param index Index to place item
   * @param value Value to place at Index
   */
  void insert(size_t index, T value) {
    // Initial Tests
    _checkValidSize();
    _checkOutOfBounds(index);

    // Go to Node at index
    Node<T> *curr = _getNodeAt(index);

    // Place new Node
    Node<T> *node = new Node<T>(curr->prev, curr, value);
    if (curr != head) {
      curr->prev->next = node;
    } else {
      head = node;
    }
    curr->prev = node;

    // Account for New Addition
    _size++;
  }

  /**
   * Removes node at given Index
   * @param index Index of Node to remove
   */
  void erase(size_t index) {
    // Initial Checks
    _checkValidSize();
    _checkOutOfBounds(index);

    // Check tail or head removal
    if (index == 0)
      pop_front();
    else if (index == _size - 1)
      pop_back();
    else {
      Node<T> *node = _getNodeAt(index);

      // Reference sibling nodes
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
      _size--;
    }
  }

  // Reverses the List
  void reverse() {
    if (!empty()) {
      Node<T> *curr = head;
      while(curr != nullptr) {
        Node<T> *next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        curr = next;
      }

      // Remap Head and Tail
      curr = head;
      head = tail;
      tail = curr;
    }
  }

  /**
   * Removes first Node with given Value
   * @param value Value to Search for
   */
  void remove_value(T value) {
    Node<T> *curr = head;

    while(curr != nullptr) {
      if (curr->data == value) {
        if (curr == head) {
          pop_front();
          return;
        }
        else if (curr == tail) {
          pop_back();
          return;
        }

        // Reference sibling nodes
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        _size--;
        return;
      }
      curr = curr->next;
    }
  }


  // DEBUG: Print List
  void print_list() {
    std::cout << "Size: " << _size << '\n';
    
    Node<T> *curr = head;
    while (curr != nullptr) {
      std::cout << curr->data << " ";
      curr = curr->next;
    }
    std::cout << '\n';
  }
};


void test1() {
  LinkedList<int> list;

  // Start off Data
  for (int i=0; i<2; i++)
    list.push_back(i);

  // Test Pop Back & Data Input
  int i = list.pop_back();
  std::cout << "Data Popped: " << i << '\n';
  list.print_list();
  
  // Test Push Front
  list.push_front(i);
  list.print_list();

  // Test Pop Front
  i = list.pop_front();
  std::cout << "Front Popped: " << i << '\n';
  list.print_list();

  // Test no Breaks
  list.pop_front();
  list.print_list();

  // Front & Backs
  list.push_back(1);
  std::cout << "Front: " << list.front() << '\n';
  std::cout << "Back: " << list.back() << '\n';
  list.push_front(2);
  std::cout << "Front: " << list.front() << '\n';
  std::cout << "Back: " << list.back() << "\n\n";
  
  list.print_list();
}

void test2() {
  LinkedList<int> list;

  // Start off Data
  for (int i = 0; i < 10; i++)
    list.push_back(i);
  list.print_list();

  // Test Index At
  int index = 9;
  std::cout << "Index at '" << index << "' = " << list.value_at(index) << '\n';

  // Inserting the Right Values in the Correct Indicies
  list.insert(0, -1);
  list.insert(0, -2);
  list.insert(0, -3);
  list.insert(list.size() - 1, 10);
  list.print_list();

  // Erasing Test
  list.erase(list.size() / 2);
  list.erase(list.size() / 2);
  list.print_list();

  // Reverse Test
  list.reverse();
  list.remove_value(9);
  list.print_list();

  index = 4;
  std::cout << "Index '" << index << "' from Tail = " << list.value_n_from_end(index) << '\n';
}

int main() {
  test1();
  test2();
  return 0;
}