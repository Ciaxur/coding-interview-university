#include <iostream>

// MAIN INTERFACE CLASS
class Strategy { // Strategy Interface
public:
  virtual void execute() = 0; // Pure Method
};


// Multiple different Strategies
class StrategyAdd : public Strategy {
public:
  void execute() {
    std::cout << "Executing Add...\n";
  }
};

// Multiple different Strategies
class StrategySub : public Strategy {
public:
  void execute() {
    std::cout << "Executing Subtraction...\n";
  }
};
