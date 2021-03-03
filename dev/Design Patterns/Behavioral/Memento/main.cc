#include "includes/Editor.h"
#include "includes/CareTaker.h"
using namespace std;

int main() {
  Editor editor;
  CareTaker command(&editor);

  fmt::print("Initial Editor State:\n");
  editor.print();
  
  editor.inputText("Text");
  editor.moveMouse(50, 50);
  editor.print();

  // Backup
  fmt::print("Backing up...\n");
  command.backup();
  editor.print();

  // Change State
  editor.inputText("New Data");
  editor.moveMouse(520, 100);
  editor.print();
  
  // Restore State
  fmt::print("Restoring...\n");
  command.restore();
  editor.print();
  


  return 0;
}