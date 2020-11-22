#include <iostream>
#include <tuple>
#include <math.h>


/**
 * Checks if given value 'n' is Prime
 * @param n Integer to check if Prime
 * @returns Boolean indicating if Prime
 */
bool isPrimeNumber(int n) {
  bool isPrime = true;

  for (int i = 2; i <= n / 2; i++) {
    if (n % i == 0) {
      isPrime = false;
      break;
    }
  }
  return isPrime;
}

template< typename KEY, typename VALUE >
class HashTable {
  private:
    using KeyValuePair = std::pair<KEY, VALUE>;
    KeyValuePair **table = nullptr;   // Array of Pair Pointers
    std::size_t prime = 7;            // Table Size
    std::size_t length = 0;           // Table Content
  
    /**
     * Generates a Prime value between given
     *  range
     * @param lowerBound - Lower bound Range
     * @param upperBound - Upper bound Range
     */
    int generatePrime(int lowerBound, int upperBound) {
      if (lowerBound > upperBound) return -1;

      for (int i = lowerBound; i < upperBound; i++) {
        if (isPrimeNumber(i)) {
          return i;
        }
      }
      // No Prime Found
      return -1;
    }

    /**
     * Frees up all the Pointers inside
     *  the table and the table itself
     */
    void _deleteTable() {
      if (table) {
        for (size_t i = 0; i < prime; i++) {
          if(table[i])
            delete table[i];
        }
        delete[] table;
      }
    }

    /**
     * Hash Function for given Key
     * @param k Key to hash
     * @param m Prime Number
     */
    int _hash(KEY k, size_t m) {
      uintptr_t keyAddr = reinterpret_cast<uintptr_t>(k);
      return keyAddr % m;
    }


    /**
     * Adds a new Key Value pair to the Hash Table
     * @param key The Unique Key
     * @param value The Value of the Pair
     * @param m Prime Number for Table Size
     * @param table The table to add to
     * @returns Boolean true if stored, false if key already exist
     */
    bool _add(KEY key, VALUE value, std::size_t m, KeyValuePair **table) {
      // Hash the Key Given
      int hash = _hash(key, m);

      // Check for Collision
      if (table[hash]) {    // Collision!
        // Check if Key is Already in Table
        KeyValuePair *pair = table[hash];
        if (pair->first == key) return false;
      
        // Linearly Probe
        for (size_t i = hash; i < hash + prime; i++) {
          // Loop Around the Array
          if (!table[i%prime]) {  // Free Spot
            table[i%prime] = new KeyValuePair(key, value);
            break;
          }
        }
      }
      else {                // No Collision!
        table[hash] = new KeyValuePair(key, value);
      }

      // Keep Count
      length++;
      return true;
    }

    /**
     * Generates a new Table with new Size, moving
     *  all the items over to the new Table
     */
    void regenerateTable() {
      // Get new Prime Number
      int newPrime = generatePrime(prime * 2, prime * 4);
      length = 0;     // Reset Length
      
      // Construct new Table
      KeyValuePair **newTable = new KeyValuePair*[newPrime];

      // Check if Table was Assigned
      if (!table) {
        table = newTable;
        return;
      }

      // Move over all Items
      for (size_t i = 0; i < prime; i++) {
        if(table[i] != nullptr) {
          KeyValuePair *pair = table[i];
          _add(pair->first, pair->second, newPrime, newTable);
        }
      }

      // Assign new Table
      _deleteTable();
      table = newTable;
      prime = newPrime;
    }

  public:
    /**
     * Generates the Table with size m being
     *  a Prime Number
     */
    HashTable() {
      // Construct the Table
      regenerateTable();
    }

    ~HashTable() {
      _deleteTable();
    }
    
    /**
     * Prints out entire Table Content
     */
    void print() {
      if (!table) {
        std::cout << "No Table Defined!\n";
        return;
      }

      std::cout << "Table Size: " << length << '\n';
      for (size_t i = 0; i < prime; i++) {
        KeyValuePair *pair = table[i];
        
        if (pair)
          std::cout << "Table[" << i << "] = { " << pair->first << ", " << pair->second << " }\n";
        else
          std::cout << "Table[" << i << "] = { NULL }\n";
      }
      std::cout << std::endl;
    }  

    /**
     * Adds given Key Value pairs to the Table
     * @param key The Key of Pair
     * @param value The Value of Pair
     */
    void add(KEY key, VALUE value) {
      // Grow Based on Table Content
      if (((double)length / prime) >= (0.75)) {   // 3/4 Size Reached, Resize!
        regenerateTable();
        std::cout << "INFO: TABLE RESIZED TO " << prime << std::endl;
      }


      // Add Pair
      if (!this->_add(key, value, prime, table)) {
        std::cout << "Key '" << key << "' Already Exists!\n";
      }
    }


    /**
     * Checks if given Key exists
     * @param key Key to check
     * @return State of finding the Key
     */
    bool exists(KEY key) {
      int hash = _hash(key, prime);

      // Found
      if (table[hash] && table[hash]->first == key)
        return true;
      
      // Collision
      else if (table[hash]) {
        std::cout << "Collision: " << table[hash]->first << '\n';

        // Linear Probe Search
        for (size_t i = hash; i < hash + prime; i++) {
          if (!table[i%prime])
            return false;
          
          if (table[i%prime]->first == key)
            return true;
        }
      }

      // Not Found
      return false;
    }

    // Returns the Size of the Contents in Table
    size_t size() { return length; }
};


int main() {
  HashTable<const char *, int> table;
  
  const size_t key_size = 4;
  std::string keys[key_size] = { "teapot", "jeff", "megan", "bill" };

  
  table.print();
  for (int i = 0; i < key_size; i++) {
    table.add(keys[i].c_str(), i);
  }
  table.print();


  for (int i = 0; i < key_size; i++) {
    std::cout << "Exists(" << keys[i] << ")? ";
    if (table.exists(keys[i].c_str())) {
      std::cout << "Exists!\n";
    } else {
      std::cout << "Doesn't Exist\n";
    }
  }


  return 0;
}