#include "includes/Snapshot.h"


Momento::Momento(Editor *editor, int curX, int curY, std::string text) {
  this->editor = editor;
  this->curX = curX;
  this->curY = curY;
  this->text = text;
}

void Momento::restore() {
  editor->inputText(text);
  editor->moveMouse(curX, curY);
}


