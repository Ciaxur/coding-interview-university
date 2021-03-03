#include <bits/stdc++.h>
#include "AbstractFactory.hpp"
using namespace std;

int main() {
  // DarkMode Application
  Application app_dark(new DarkModeFactory());
  app_dark.run();

  // LightMode Application
  Application app_light(new LightModeFactory());
  app_light.run();
  
  return 0;
}