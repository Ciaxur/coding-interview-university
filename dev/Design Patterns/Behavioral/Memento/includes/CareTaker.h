#pragma once
#include <stack>
#include "Snapshot.h"
#include "Editor.h"

// CARETAKER CLASS
class CareTaker {
private:
  std::stack<Momento> history;
  Editor *editor;
public:
  CareTaker(Editor *editor);
  void backup();
  void restore();
};