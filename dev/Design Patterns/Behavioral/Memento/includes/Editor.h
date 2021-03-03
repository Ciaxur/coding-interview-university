#pragma once
#include <fmt/format.h>
#include <iostream>
#include "Snapshot.h"
class Momento;

// CLIENT CLASS (Originator)
class Editor {
private:
  int curX, curY;
  std::string text;

public:
  Editor();

  Momento createSnapshot();

  void moveMouse(int newX, int newY);
  void inputText(std::string inputText);
  void print();
};