#include <fmt/format-inl.h>

// Forward Decleration
class Shape;
class Dot;
class Circle;
class Square;


// VISITOR IMPLEMENTATION
class Visitor {
public:
  void visit(Dot *dot) {
    fmt::print("Visiting Dot...\n");
  }
  void visit(Circle *circ) {
    fmt::print("Visiting Circle...\n");
  }
  void visit(Square *square) {
    fmt::print("Visiting Square...\n");
  }
};


// SHAPE CLASSES
class Shape {
public:
  virtual void accept(Visitor &v) = 0;
};


class Dot: public Shape {
public:
  // ...aside from other methods
  void accept(Visitor &v) {
    v.visit(this);
  }
};

class Circle: public Dot {
public:
  // ...aside from other methods
  void accept(Visitor &v) {
    v.visit(this);
  }
};

class Square: public Shape {
public:
  // ...aside from other methods
  void accept(Visitor &v) {
    v.visit(this);
  }
};




