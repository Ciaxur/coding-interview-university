#include <bits/stdc++.h>
#include <fmt/format-inl.h>
#include "Cell.hpp"
using namespace std;


int main() {
  // SIMPLE EXAMPLE
  fmt::print("== By Constructor ==\n");
  Cell c1{10};
  Cell anotherC1 = c1;
  Cell c2{200};
  Cell c2_clone{c2};

  // Modify C1
  c1.setLifespan(588);
  Cell c1_clone = Cell::clone(c1);

  fmt::print("Cell[{}].lifespan = {}\n", c1.getID(), c1.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", anotherC1.getID(), anotherC1.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", c2.getID(), c2.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", c2_clone.getID(), c2_clone.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", c1_clone.getID(), c1_clone.getLifespan());


  // REGISTRY EXAMPLE
  fmt::print("\n== By Registery ==\n");
  CellRegistry cellRegistry;

  // Add Prototype to Registry
  cellRegistry.addItem("Initial Cell", c1);
  cellRegistry.addItem("Second Homie", c2);

  // Get Copies of Prototype
  Cell cr1 = cellRegistry.getByKey("Initial Cell");
  Cell cr2 = cellRegistry.getById(2);             // Not found. Creates new One
  Cell cr3 = cellRegistry.getById(3);             // Gets Cell 3, which is c2
  Cell cr4 = cellRegistry.getByKey("Not found");  // Creates a New One | Not found in Registry


  fmt::print("Cell[{}].lifespan = {}\n", cr1.getID(), cr1.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", cr2.getID(), cr2.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", cr3.getID(), cr3.getLifespan());
  fmt::print("Cell[{}].lifespan = {}\n", cr4.getID(), cr4.getLifespan());
  
  return 0;
}