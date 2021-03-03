#include "./FactoryMethod.hpp"


int main() {
  ProductBFactory factory;
  ProductB *pa = (ProductB*)factory.createProduct();
  pa->doStuff();
  delete pa;
  
  return 0;
}