#include <bits/stdc++.h>
#include <fmt/format-inl.h>
#include "Composite.hpp"
using namespace std;

int main() {
  GraphicEditor editor;

  // Create some Dots!
  Dot d1{1, 1};
  Dot d2{2, 2};
  Dot d3{20, 20};

  // Create some a Graphic Compound
  Dot d4{55, 20};
  Dot d5{105, 120};
  Dot d6{115, 130};
  CompoundGraphic g1{&d4, &d5, &d6};

  // Add all to Editor
  editor.addGraphic({ &d1, &d2, &d3, &g1 });
  
  // Draw them Grahpics!
  editor.draw();

  return 0;
}