#include <bits/stdc++.h>
using namespace std;


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

/**
 * Generates a Prime value between given
 *  range
 * @param lowerBound - Lower bound Range
 * @param upperBound - Upper bound Range
 */
int generatePrime(int lowerBound, int upperBound) {
  if (lowerBound > upperBound)
    return -1;

  for (int i = lowerBound; i < upperBound; i++) {
    if (isPrimeNumber(i)) {
      return i;
    }
  }
  // No Prime Found
  return -1;
}



template< typename KEY, typename VALUE >
class HashTable {
private:    // Key Value Pair Structure
  struct KeyValuePair {
    KeyValuePair(uintptr_t hash, KEY key, VALUE value): hash(hash), first(key), second(value), removed(false) {};
    
    KEY       first;      // Copy of the Key
    VALUE     second;     // Copy of the Value
    uintptr_t hash;       // Hashed Data for the Original Key
    bool      removed;    // Flaged as Removed for Linear Search to Collide
  };
  
private:    // Private Variables
  KeyValuePair **table = nullptr;   // Array of Pair Pointers
  uint32_t prime = 3;               // Table Size
  size_t length = 0;                // Table Content
  
private:    // Private Methods
  /**
   * Hashes given Key to an index in the table
   *  given the size of the array
   * @param k Key to Hash
   */
  uintptr_t _hash(KEY &k) {
    uintptr_t addrOfKey = reinterpret_cast<uintptr_t>(&k);
    return addrOfKey;
  }

  /**
   * Hashes given a Contant Key to an index in the table
   *  given the size of the array
   * @param k Key to Hash
   */
  uintptr_t _hash(const KEY &k) {
    uintptr_t addrOfKey = reinterpret_cast<uintptr_t>(k);
    return addrOfKey;
  }

  /**
   * Inner funciton that checks based on a hashed key
   *  if the key exists or not
   * @throws If key not found
   * @returns Pair of Value and index of the Key
   */
  pair<VALUE, uint32_t> _get(uintptr_t hash, KEY key) {
    uint32_t hashedIndex = hash % prime;
    
    // Found
    if (table[hashedIndex] && !table[hashedIndex]->removed && table[hashedIndex]->first == key)
      return { table[hashedIndex]->second, hashedIndex };

    // Collision
    else if (table[hashedIndex]) {
      // Linear Probe Search
      for (size_t i = hashedIndex; i < hashedIndex + prime; i++) {
        if (!table[i % prime])
          throw out_of_range("Key not found");

        if (table[i % prime]->first == key && !table[i % prime]->removed)
          return { table[hashedIndex]->second, i % prime };
      }
    }

    // Not Found
    throw out_of_range("Key not found");
  }

  /**
   * Adds a new Key Value pair to the Hash Table
   * @param hash The Hashed Value
   * @param key The Key Value
   * @param value The Value of the Pair
   * @param m Prime Number for Table Size
   * @param table The table to add to
   * @returns Boolean true if stored, false if key already exist
   */
  bool _add(uintptr_t hash, KEY key, VALUE value, uint32_t m, KeyValuePair **table) {
    uint32_t hashedIndex = hash % m;
    
    // DEBUG: PRINTS
    cout << "_ADD: Hashed key '" << key << "' = " << hash << '\n';
    cout << "_ADD: Hashed index = " << hashedIndex << '\n';
    cout << "_ADD: Checking for collisions...\n";

    // Collision!
    if (table[hashedIndex] && !table[hashedIndex]->removed) {
      // Check if the Key is already in the Table
      KeyValuePair *pair = table[hashedIndex];

      if (pair->first == key) { // Overwrite Value
        pair->second = value;
        return true;
      }

      // DEBUG: PRINTS
      cout << "_ADD: Linearly searching...\n";
      
      // Linearly Probe
      for (size_t i = hashedIndex; i < hashedIndex + prime; i++) {
        // Loop around the array
        if (!table[i%prime]) {    // Free Spot found
          table[i%prime] = new KeyValuePair(hash, key, value);
          break;
        }
      }
    } 

    // Marked as Removed | Free up & Replace
    else if (table[hashedIndex] && table[hashedIndex]->removed) {
      delete table[hashedIndex];
      table[hashedIndex] = new KeyValuePair(hash, key, value);
    }

    // No Collision!
    else {
      table[hashedIndex] = new KeyValuePair(hash, key, value);
    }

    // Keep Count
    length++;
    return true;
  }

  /**
   * Inline method for removing given key
   * @throws If key not found
   * @param hash Hashed value of Key
   * @param key Key value
   */
  inline void _remove(uintptr_t hash, KEY key) {
    pair<VALUE, uint32_t> p = _get(hash, key);

    // DEBUG: PRINTS
    cout << "_REMOVE: Removing key '" << key << "'\n";

    // Mark for Removal
    table[p.second]->removed = true;
    length--;
  }

  /**
   * Pre-Check to Adding a Key-Value pair to the
   *  table checking if the table requires a Resize
   */
  void _preAddChecks() {
    // Grow Based on Table Content
    if (((double)length / prime) >= (0.75)) { // 3/4 Size Reached, Resize!
      regenerateTable();
      cout << "INFO: TABLE RESIZED TO " << prime << endl;
    }
  }


  /**
   * Frees up all the Pointers inside
   *  the table and the table itself
   */
  void _deleteTable() {
    if (table) {
      for (size_t i = 0; i < prime; i++) {
        if (table[i])
          delete table[i];
      }
      delete[] table;
    }
  }

  /**
   * Generates a new Table with new Size, moving
   *  all the items over to the new Table
   */
  void regenerateTable() {
    // Generate new Prime Number
    uint32_t newPrime = generatePrime(prime * 2, prime * 4);
    length = 0;
    
    // DEBUG: PRINTS
    cout << "REGEN-TABLE: Old Prime: " << prime << " -> New Prime: " << newPrime << '\n';

    // Construct new Table
    KeyValuePair **newTable = new KeyValuePair*[newPrime];

    // Check if initial Table Assigned
    if (!table) {
      // DEBUG: PRINTS
      cout << "REGEN-TABLE: Setting initial table\n";
      
      table = newTable;
      return;
    }

    // DEBUG: PRINTS
    cout << "REGEN-TABLE: Moving over items from table to new table...\n";

    // Move over all Items
    for (size_t i = 0; i < prime; i++) {
      if (table[i] != nullptr) {
        KeyValuePair *pair = table[i];
        _add(pair->hash, pair->first, pair->second, newPrime, newTable);
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
    regenerateTable();
  }

  ~HashTable() {
    _deleteTable();
  }


  /**
   * Checks if given Key exists
   * @param key Key to check
   * @return State of finding the Key
   */
  bool exists(KEY &key) noexcept {
    uintptr_t hash = _hash(key);

    try {
      _get(hash, key);
      return true;
    } catch(exception &e) {
      return false;
    }
  }

  /**
   * Checks if given a Constant Key exists
   * @param key Key to check
   * @return State of finding the Key
   */
  bool exists(const KEY &key) noexcept {
    uintptr_t hash = _hash(key);

    try {
      _get(hash, key);
      return true;
    } catch (exception &e) {
      return false;
    }
  }

  /**
   * Adds Key-Value pair based on
   *  address of a Reference
   * @param key Reference to the Key
   * @param value The value associated with key
   */ 
  void add(KEY &key, VALUE value) {
    // Pre-Check
    _preAddChecks();
    
    // Add Pair
    this->_add(_hash(key), key, value, prime, table);
  }

  /**
   * Adds Key-Value pair based on
   *  address of a Constant Reference
   * @param key Reference to the Key
   * @param value The value associated with key
   */ 
  void add(const KEY &key, VALUE value) {
    // Pre-Check
    _preAddChecks();
    
    // Add Pair
    this->_add(_hash(key), key, value, prime, table);
  }


  /**
   * Attempts to get the value of the given Key
   * @param key Key Reference to get value of
   * @throws Exception if key not found
   */ 
  VALUE get(KEY &key) {
    uintptr_t hash = _hash(key);
    return _get(hash, key).first;
  }

  /**
   * Attempts to get the value of the given Key
   * @param key Constant Key Reference to get value of
   * @throws Exception if key not found
   */ 
  VALUE get(const KEY &key) {
    uintptr_t hash = _hash(key);
    return _get(hash, key).first;
  }

  /**
   * Remove given Key from Hash Table
   * @throws If key doesn't exist
   * @param key key
   */
  void remove(KEY &key) {
    // Obtain info about the Key-Value Pair
    uintptr_t hash = _hash(key);
    _remove(hash, key);
  }

  /**
   * Remove given Key from Hash Table
   * @throws If key doesn't exist
   * @param key Constant key
   */
  void remove(const KEY &key) {
    // Obtain info about the Key-Value Pair
    uintptr_t hash = _hash(key);
    _remove(hash, key);
  }

  /**
   * Prints out entire Table Content
   */
  void print() {
    if (!table) {
      cout << "No Table Defined!\n";
      return;
    }

    cout << "Table Size: " << length << '\n';
    for (size_t i = 0; i < prime; i++) {
      KeyValuePair *pair = table[i];

      if (pair) {
        cout << "Table[" << i << "] = { "
             << pair->first << ": " << pair->second
             << ", hash: " << pair->hash
             << ", removed: " << pair->removed << " }\n";
      } else
        cout << "Table[" << i << "] = { NULL }\n";
    }
    cout << endl;
  }
};



int main() {
  HashTable<const char*, int> m1;

  // Add Test
  m1.add("key", 1);
  m1.add("key2", 38);
  m1.add("key3", 18);
  m1.add("matilda", 8);
  m1.remove("key3");
  m1.add("key3", 19);
  m1.remove("matilda");

  // Exist Test
  cout << "\n'key' exists? " << boolalpha << m1.exists("key") << '\n';
  cout << "'key13' exists? " << boolalpha << m1.exists("key13") << '\n';
  cout << "'key3' exists? " << boolalpha << m1.exists("key3") << '\n';
  cout << "'matilda' exists? " << boolalpha << m1.exists("matilda") << '\n';
  
  // Get Test
  cout << "Get key 'key' = " << m1.get("key") << '\n';
  cout << "Get key 'key2' = " << m1.get("key2") << '\n';
  
  cout << "\n\n=== TABLE PRINT ===\n";
  m1.print();

  return 0;
}