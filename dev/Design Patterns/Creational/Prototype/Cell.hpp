/*
  Prototype by having a Clone Class Method
*/
class Cell {
private:  // Private Static Variables
  static unsigned long _id;


private:
  int lifespan;
  unsigned long id;
  
public:
  // CONSTRUCTORS
  Cell(const Cell &cell): lifespan(cell.lifespan), id(++Cell::_id) {}   // Used for clone()
  Cell(int lifespan): lifespan(lifespan), id(++Cell::_id) {}
  Cell(): lifespan(0), id(++Cell::_id) {}

  // ACTION METHODS
  const Cell clone() {
    return Cell(*this);
  }

  // GETTERS
  unsigned long long getID() {
    return id;
  }

  int getLifespan() {
    return lifespan;
  }
  
  // SETTERS
  void setLifespan(int newLifespan) {
    this->lifespan = newLifespan;
  }

  
  // STATIC METHODS
  static Cell clone(Cell &cell) {
    return Cell(cell);
  }

  
};

unsigned long Cell::_id = 0;


/*
  Prototype by having a Registry of frequent Objects
*/
#include <unordered_map>
#include <iostream>

class CellRegistry {
private:
  std::unordered_map<const char *, Cell&> registry;

public:
  // CONSTRUCTORS
  CellRegistry() {}
  
  // GETTERS/SETTERS
  void addItem(const char *key, Cell &cell) {
    this->registry.insert({ key, cell });
  }

  Cell getById(int id) {
    for (auto &pair: this->registry) {
      if (pair.second.getID() == id)
        return pair.second.clone();
    }
    return Cell();
  }

  Cell getByKey(const char *key) {
    try {
      return this->registry.at(key).clone();
    } catch(std::out_of_range &e) {
      return Cell();
    }
  }
  
};