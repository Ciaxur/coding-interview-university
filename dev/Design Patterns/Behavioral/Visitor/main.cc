#include "Shapes.hpp"

int main() {
  Dot dot;
  Circle circ;
  Square sq;
  Visitor v;

  // Accept Visitations
  dot.accept(v);
  circ.accept(v);
  sq.accept(v);
  

  return 0;
}