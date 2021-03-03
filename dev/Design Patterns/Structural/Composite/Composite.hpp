#include <vector>
#include <fmt/format.h>

// COMPONENT INTERFACE
class Graphic {
public:
  virtual void draw() = 0;
};


// LEAF CLASS
class Dot: public Graphic {
private:
  int x, y;
public:
  Dot(int x, int y): x(x), y(y) {}
  void draw() {
    fmt::print("Dot: Drawing on {}, {}\n", x, y);
  }
};


// COMPOSITE CLASS
class CompoundGraphic: public Graphic {
private:
  std::vector<Graphic*> children;
public:
  CompoundGraphic() {}
  CompoundGraphic(std::initializer_list<Graphic*> initList): children{initList} {}

  void add(Graphic *graphic) {
    children.push_back(graphic);
  }

  void draw() {
    for (Graphic* g: children) {
      fmt::print("Graphic: Drawing Children...\n");
      g->draw();
    }
  }
};


// CLIENT CLASS
class GraphicEditor {
private:
  std::vector<Graphic*> graphics;
public:
  void addGraphic(Graphic *graphic) {
    graphics.push_back(graphic);
  }

  void addGraphic(std::initializer_list<Graphic*> initList) {
    for (Graphic *g : initList)
      graphics.push_back(g);
  }

  void draw() {
    for (Graphic *g: graphics) {
      fmt::print("GraphicEditor: Drawing Graphic...\n");
      g->draw();
    }
  }

};