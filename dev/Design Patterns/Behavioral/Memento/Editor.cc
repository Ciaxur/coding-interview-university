#include "includes/Editor.h"

Editor::Editor(): curX(0), curY(0) {}

void Editor::moveMouse(int newX, int newY) {
  curX = newX;
  curY = newY;
}

void Editor::inputText(std::string inputText) {
  text = inputText;
}
void Editor::print() {
  fmt::print("Cursor: {}, {}\n", curX, curY);
  fmt::print("Text: {}\n", text);
}

Momento Editor::createSnapshot() {
  return Momento{ this, curX, curY, text };
}