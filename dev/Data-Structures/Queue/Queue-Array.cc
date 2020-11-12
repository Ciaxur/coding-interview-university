#include <iostream>
#include <stdexcept>

template< typename T >
class Queue {
  private:
    T *_data;
    size_t _capacity;
    size_t _length;
  

  public:
    /**
     * Initializes the Queue with a Default size of 10
     */
    Queue() {
      _capacity = 10;
      _length = 0;
      _data = new T[_capacity];
    }

    /**
     * Predefined Size of the Queue
     * @param size The size of the Queue to pre-allocate
     */
    Queue(size_t size) {
      _capacity = size;
      _length = 0;
      _data = new T[_capacity];
    }

    // Free/Clean up Space
    ~Queue() {
      delete[] _data;
    }

    /**
     * Returns the empty state of the Queue
     */
    bool empty() {
      return _length == 0;
    }

    /**
     * Returns the full state of the Queue
     */
    bool full() {
      return _length == _capacity;
    }


    /**
     * Adds item to the end of the Array (if available)
     * @param val Value to add
     */
    void enqueue(T val) {
      // Quick Validation
      if (_length == _capacity) {
        throw std::length_error("Queue is Full");
      }

      // Add Item
      _data[_length++] = val;
    }

    /**
     * Returns the Value and remvoes it from the end
     */
    T dequeue() {
      // Quick Validation
      if (_length == 0) {
        throw std::length_error("No Items in Queue");
      }
      
      T val = _data[--_length];
      return val;
    }


    // DEBUG: Prints entire Data
    void print() {
      std::cout << "Data[ ";
      for (size_t i = 0; i < _length; i++) {
        std::cout << _data[i] << ' ';
      }
      std::cout << "]\n";
      std::cout << "Size: " << _length << '\n';
    }
};



int main () {
  Queue<int> queue;
  queue.enqueue(5);
  queue.enqueue(1);
  queue.print();

  int val = queue.dequeue();
  queue.print();
  std::cout << "Dequeued Item: " << val << '\n';
  
  return 0;
}