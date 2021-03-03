#include <bits/stdc++.h>
#include "Strategy.hpp"
using namespace std;


class Context {
private:
  Strategy *strategy;   // Holds a Type of Strategy

public:
  Context(Strategy *st): strategy(st) {}
  Context(): strategy(nullptr) {}
  ~Context() {
    if (strategy) delete strategy;
  }


  void execute() {
    if (this->strategy)
      this->strategy->execute();
    else
      cout << "No Set Strategy...\n";
  }
  
  void setStrategy(Strategy *st) {
    this->strategy = st;
  }
};

int main() {
  Strategy *st = new StrategyAdd();
  Context ctx(st);
  ctx.execute();
  return 0;
}