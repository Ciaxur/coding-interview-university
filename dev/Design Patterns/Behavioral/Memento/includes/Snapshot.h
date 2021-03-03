#pragma once
#include <bits/stdc++.h>
#include "Editor.h"
class Editor;

// MOMENTO/SNAPSHOT CLASS
class Momento {
private:
  Editor *editor;
  int curX, curY;
  std::string text;

public:
  Momento(Editor *editor, int curX, int curY, std::string text);
  void restore();
};