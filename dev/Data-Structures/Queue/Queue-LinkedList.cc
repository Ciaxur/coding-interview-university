#include <list>
#include <iostream>

template< typename T > 
class Queue {
  private:
    std::list<T> _list;   // Doubly Linked List
  
  public:
    void enqueue(T val) {
      _list.push_back(val);
    }

    T dequeue() {
      T val = _list.back();
      _list.pop_back();
      return val;
    }
  
    bool empty() {
      return _list.empty();
    }



    // DEBUG: Print out entire List
    void print() {
      std::cout << "List: [ ";
      for (const T elt : _list) {
        std::cout << elt << " ";
      }
      std::cout << "]\n";
    }
};


int main() {
  Queue<int> queue;

  queue.enqueue(5);
  queue.print();
  int val = queue.dequeue();
  queue.print();
  std::cout << "Dequeued: " << val << '\n';
  


  
  return 0;
}