#include <bits/stdc++.h>
#include "Singleton.hpp"
using namespace std;


int main() {
  Engine *engine = Engine::createEngine();
  engine->printId();

  for (int i=0; i<10; i++)
    Engine::createEngine()->printId();


  Engine::destroyInstance();
  return 0;
}