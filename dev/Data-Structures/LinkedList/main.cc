#include <iostream>
#include <stdexcept>
#include "LinkedList.hpp"


void test1() {
  LinkedList<int> list;

  // Start off Data
  for (int i=0; i<2; i++)
    list.push_back(i);

  // Test Pop Back & Data Input
  int i = list.pop_back();
  std::cout << "Data Popped: " << i << '\n';
  list.print_list();
  
  // Test Push Front
  list.push_front(i);
  list.print_list();

  // Test Pop Front
  i = list.pop_front();
  std::cout << "Front Popped: " << i << '\n';
  list.print_list();

  // Test no Breaks
  list.pop_front();
  list.print_list();

  // Front & Backs
  list.push_back(1);
  std::cout << "Front: " << list.front() << '\n';
  std::cout << "Back: " << list.back() << '\n';
  list.push_front(2);
  std::cout << "Front: " << list.front() << '\n';
  std::cout << "Back: " << list.back() << "\n\n";
  
  list.print_list();
}

void test2() {
  LinkedList<int> list;

  // Start off Data
  for (int i = 0; i < 10; i++)
    list.push_back(i);
  list.print_list();

  // Test Index At
  int index = 9;
  std::cout << "Index at '" << index << "' = " << list.value_at(index) << '\n';

  // Inserting the Right Values in the Correct Indicies
  list.insert(0, -1);
  list.insert(0, -2);
  list.insert(0, -3);
  list.insert(list.size() - 1, 10);
  list.print_list();

  // Erasing Test
  list.erase(list.size() / 2);
  list.erase(list.size() / 2);
  list.print_list();

  // Reverse Test
  list.reverse();
  list.remove_value(9);
  list.print_list();

  index = 4;
  std::cout << "Index '" << index << "' from Tail = " << list.value_n_from_end(index) << '\n';
}

int main() {
  test1();
  test2();
  return 0;
}