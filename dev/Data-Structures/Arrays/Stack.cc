/**
 * Implementing a Stack using Arrays
 */

#include <iostream>
#include <stdexcept>

template< typename T >
class Stack {
  private:
    T *_data;
    size_t _capacity;
    size_t _length;
  
  public:
    Stack() {
      // Default Size
      _capacity = 10;
      _length = 0;
      _data = new T[10];
    };

    Stack(size_t size) {
      _length = 0;
      _capacity = size;
      _data = new T[_capacity];
    }

    // Clean up 
    ~Stack() {
      delete[] _data;
    }

    bool empty() {
      return _length == 0;
    }

    void push(T value) {
      // Can't push no more!
      if (_length == _capacity) {
        throw std::out_of_range("Stack is full");
      }
      
      _data[_length++] = value;
    }

    T pop() {
      // No data to pop
      if (_length == 0) {
        throw std::range_error("No Data in Stack");
      }
      
      T val = _data[--_length];
      return val;
    }

    void resize(size_t newSize) {
      // Copy data into a new Array
      T *newData = new T[newSize];

      for (size_t i = 0; i < _length; i++)
        newData[i] = _data[i];

      _capacity = newSize;
      delete[] _data;
      _data = newData;
    }

    const constexpr size_t capacity() {
      return _capacity;
    }

    const constexpr size_t length() {
      return _length;
    }

    T head() {
      if (_length == 0) {
        throw std::out_of_range("No Data in Stack");
      }
      return _data[_length - 1];
    }


    // DEBUG: Print Entire Array
    void printArray() {
      std::cout << "Stack: " << (empty() ? "EMPTY" : "");
      for (size_t i = 0; i < _length; i++) {
        std::cout << _data[i] << ' ';
      }

      std::cout << '\n';
    }
};


int main() {
  Stack<int> stack;
  std::cout << stack.length() << '\n';
  for (int i=0; i<5; i++)
    stack.push(i);

  stack.pop();
  
  stack.printArray();

  return 0;
}