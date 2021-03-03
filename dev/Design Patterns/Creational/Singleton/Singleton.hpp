#include <iostream>
using namespace std;

class Engine {
  private:
    static Engine *instance;
    static int _id;

  private:
    int id;
    Engine(int _id): id(_id) {}

  public:
    ~Engine() {
      cout << "Destroying Remains!\n";
    }
  
    static Engine *createEngine() {
      if (!instance)
        instance = new Engine(++_id);
      return instance;
    }

    static void destroyInstance() {
      if (instance) {
        delete instance;
        instance = nullptr;
        --_id;
      }
    }

    void printId() {
      cout << "My ID: " << id << '\n';
    }
  
};

Engine *Engine::instance = nullptr;
int Engine::_id = 0;
