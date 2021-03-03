#include <bits/stdc++.h>
#include <fmt/format-inl.h>
#include "Shapes.hpp"
using namespace std;

int main() {
  RoundHole rh{30.0f};
  RoundPeg  rp{10.0f};
  SquarePeg sp{10.0f};

  fmt::print("Round Peg of radius '{}' fits? {}\n", rp.getRadius(), rh.fits(&rp));

  // Construct an Adapter for Square Peg
  AdapterSquarePeg ap{sp};
  fmt::print("Square Peg of width '{}' or radius '{:.2f}' fits? {}\n", sp.getWidth(), ap.getRadius(), rh.fits(&ap));

  return 0;
}