#include "includes/CareTaker.h"

CareTaker::CareTaker(Editor *editor) {
  this->editor = editor;
}

void CareTaker::backup() {
  history.push(editor->createSnapshot());
}

void CareTaker::restore() {
  history.top().restore();
  history.pop();
}
