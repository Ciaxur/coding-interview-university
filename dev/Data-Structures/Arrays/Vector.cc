// Mutable Vector Array with automatic resizing
#include <iostream>
#include <stdexcept>

template< typename T >
class Vector {
  private:
    size_t _capacity = 16;     // Keep track of Allocated Size
    size_t _size = 0;
    T *_data;              // Allocated Data Stored


    // Increases the Capacity of the Array by 2
    void _resize(size_t newCapacity) {
      // Reallocate Space, Copying Data over
      _capacity = newCapacity; // Double the Size
      T *newData = new T[_capacity];

      // Copy data from Previous Array
      for (size_t i = 0; i < _size; i++) {
        newData[i] = _data[i];
      }

      // Clean up
      delete[] _data;
      _data = newData;
    }

  public:
    // Default Constructor Allocate 16
    Vector() {
      _data = new T[this->_capacity];
    }

    /**
     * Specified Size
     * @param size The Size of which to Allocate for Array
     */
    Vector(size_t size) {
      this->_capacity = size;
      _data = new T[size];
    }

    // Returns the total Elements in Array
    const size_t size() {
      return this->_size;
    }
  
    // Returns Number of Elements Array can Hold
    const size_t capacity() {
      return this->_capacity;
    }

    // Empty State?
    bool is_empty() {
      return this->_size == 0;
    }

    
    /**
     * Returns Element at Index
     * @param index Index of Element to Return
     * @throw Out of Bounds Exception
     */
    T at(size_t index) {
      if (index < 0 || index > _capacity) {
        throw std::out_of_range("Index is out of Range!");
      }

      return _data[index];
    }

    /**
     * Adds item to Array's Tail
     * @param item Item to push onto Array
     */
    void push(T item) {
      // Allocate Space as Needed
      if (_size >= _capacity) {
        _resize(_capacity * 2);   // Double Size
      }

      // Add item at the End
      _data[_size] = item;
      _size++;
    }

    
    /**
     * Adds item at Index shifting elements right
     * @param index Index to place item at
     * @param item Item to Place at Index
     */
    void insert(size_t index, T item) {
      // Check if Index Valid, else EXPLODE
      if (index < 0 || index > _capacity) {
        throw std::out_of_range("Index is out of Range!");
      }

      // Allocate Space as needed
      if (_size >= _capacity) {
        _resize(_capacity * 2); // Double Size!
      }


      // Place Item & Account for it
      T temp1 = _data[index];   // Replaced Item
      _data[index] = item;
      _size++;

      // Shift Data to Right
      for (size_t i = index + 1; i < _size; i++) {
        T temp2 = _data[i];
        _data[i] = temp1;
        temp1 = temp2;
      }
    }

    /**
     * Prepend item at Index 0
     * @param item Item to add at head
     */
    void prepend(T item) {
      insert(0, item);
    }

    // Remove from end, return Value (Returns )
    T pop() {
      if (!is_empty()) {
        _size--;

        if ((_size / _capacity) <= 0.25)  // 1/4 of Size
          _resize(_capacity / 2);         // Half the Size
        
        return _data[_size];
      }
      
      throw std::out_of_range("No Data to Remove!");
    }

    /**
     * Removes Item at Index, shifting Elements Left
     * @param index Index to remove item from
     * @throw Out of Bounds Exception
     */
    void deleteAt(size_t index) {
      if (index < 0 || index > this->_size) {
        throw std::out_of_range("Index out of Bounds!");
      }

      // Remove Data & Account for it
      _size--;
      for (size_t i = index; i < _size; i++) {
        _data[i] = _data[i + 1];
      }
    }

    /**
     * Search & Remove item
     * @param item Item to Remove
     */
    void remove(T item) {
      for (size_t i = 0; i < _size; i++) {
        if (item == _data[i])
          deleteAt(i);
      }
    }

    /**
     * Attempts to Find Item
     * @param item Item to search for
     * @returns 1st Index of Item, -1 if not found
     */
    size_t find(T item) {
      for (size_t i = 0; i < _size; i++) {
        if (item == _data[i])
          return i;
      }
      return -1;
    }

    // Clean up after DEATH
    ~Vector() {
      delete[] _data;
    }
};



template <typename T>
void print_details(Vector<T> *vec) {
  std::cout << "Size: " << vec->size() << '\n';
  std::cout << "Capacity: " << vec->capacity() << '\n';
  std::cout << "Empty?: " << vec->is_empty() << '\n';
  std::cout << "First Element: " << vec->at(0) << '\n';

  // All Elements
  std::cout << "Data: ";
  for (size_t i=0; i<vec->size(); i++) {
    std::cout << vec->at(i) << ' ';
  }
  std::cout << "\n\n";
}

void testVec() {
  Vector<int> vec;

  // Test out Methods
  print_details<int>(&vec);

  for (int i=0; i<5; i++)
    vec.push(i);

  vec.insert(2, 4);
  vec.prepend(99);
  print_details<int>(&vec);
  std::cout << "Index of 4: " << vec.find(4) << '\n';
  vec.remove(4);
  vec.pop();
  print_details<int>(&vec);
  
}

int main() {
  testVec();
  return 0;
}