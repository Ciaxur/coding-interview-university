#include <fmt/format-inl.h>

/** INTERFACE
 * Construct of what is being "Produced" by the factory
 */
class Product {
public:
  virtual void doStuff() = 0;
};


// PRODUCTS: The the factory produces
class ProductA: public Product {
public:
  void doStuff() {
    fmt::print("ProductA: Doing Stuff...\n");
  }
};
class ProductB: public Product {
public:
  void doStuff() {
    fmt::print("ProductB: Doing Stuff...\n");
  }
};


// FACTORY
class Creator {
public:
  virtual Product* createProduct() = 0;
};

class ProductAFactory: public Creator {
public:
  Product* createProduct() {
    return new ProductA();
  }
};

class ProductBFactory: public Creator {
public:
  Product* createProduct() {
    return new ProductB();
  }
};