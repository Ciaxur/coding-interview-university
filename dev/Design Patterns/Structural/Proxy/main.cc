#include "DB_Proxy.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
  // Proxy Database
  DatabaseService *service = new DatabaseProxy();
  
  // Requests gets cached util execution is ready
  fmt::print("Proxy:\n");
  for (int i=0; i<25; i++) {
    fmt::print("[{}] -> Requested\n", i);
    service->createId(i);
  }


  // Requests get executed at request without delay
  delete service;
  fmt::print("\nNo Proxy:\n");
  service = new Database();
  for (int i=0; i<25; i++) {
    fmt::print("[{}] -> Requested\n", i);
    service->createId(i);
  }


  // Clean up...
  delete service;
  return 0;
}