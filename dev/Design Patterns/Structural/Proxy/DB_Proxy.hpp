#include <fmt/format-inl.h>
#include <stack>

// DATABASE SERVICE INTERFACE
class DatabaseService {
public:
  virtual void createId(int id) = 0;
  virtual void deleteId(int id) = 0;
  virtual int  getId()    = 0;
};


// DATABASE CLASS (No Proxy)
class Database: public DatabaseService {
private:
  int _id = 0;
  
public:
  void createId(int id) {
    _id = id;
    fmt::print("Creating ID {}\n", id);
  }
  void deleteId(int id){
    _id = id;
    fmt::print("Removing ID {}\n", id);
  }
  int getId(){
    return _id;
  }
};

// DATABASE CLASS (PROXY: Caching)
class DatabaseProxy: public DatabaseService {
private:
  int _id = 0;
  std::stack<int> ids_create;
  std::stack<int> ids_delete;
  
public:
  void createId(int id) {
    _id = id;
    ids_create.push(id);

    // Flush all
    if (ids_create.size() > 5)
      this->execute();
  }
  void deleteId(int id){
    _id = id;
    ids_delete.push(id);

    // Flush all
    if (ids_create.size() > 5)
      this->execute();
  }
  int getId(){
    return _id;
  }

  // Executes all Requests at Once
  void execute() {
    // Flush all Create Requests
    while(!ids_create.empty()) {
      int id = ids_create.top();
      fmt::print("Creating ID {}\n", id);
      ids_create.pop();
    }

    // Flush all Delete Requests
    while(!ids_delete.empty()) {
      int id = ids_delete.top();
      fmt::print("Removing ID {}\n", id);
      ids_delete.pop();
    }

  }
};