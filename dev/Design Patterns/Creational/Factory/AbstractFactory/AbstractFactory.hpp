#include <string>
#include <fmt/format-inl.h>

// CONCRETE CLASSES
class Button {
private:
  std::string name = "Button";
  
public:
  const char *getName() { return name.c_str(); }
  void setName(std::string newName) { name = newName; };

};
class Dialog {
private:
  std::string name = "Dialog";

public:
  const char *getName() { return name.c_str(); }
  void setName(std::string newName) { name = newName; };
};


// ABSTRACT FACTORY
class MainFactory {
public:
  virtual Button *createButton() = 0;
  virtual Dialog *createDialog() = 0;
};

// FACTORIES
class DarkModeFactory: public MainFactory {
public:
  Button *createButton() {
    Button *btn = new Button();

    // Modify Button for Dark Mode!
    btn->setName("Dark Button");

    return btn;
  }

  Dialog *createDialog() {
    Dialog *diag = new Dialog();

    // Modify for Dark Mode!
    diag->setName("Dark Dialog");

    return diag;
  }
};
class LightModeFactory: public MainFactory {
public:
  Button *createButton() {
    Button *btn = new Button();

    // Modify Button for Light Mode!
    btn->setName("Light Button");

    return btn;
  }

  Dialog *createDialog() {
    Dialog *diag = new Dialog();

    // Modify for Light Mode!
    diag->setName("Light Dialog");

    return diag;
  }
};


// APPLICATION
class Application {
private:
  MainFactory *factory;    // Factory used in the Application
  Button *btn;
  Dialog *diag;
  
public:
  Application(MainFactory *factory): factory(factory) {}
  Application(MainFactory &factory): factory(&factory) {}
  ~Application() {
    if (btn)  delete btn;
    if (diag) delete diag;
    if (factory) delete factory;
  }
  
  void run() {
    // Construct using given Factory
    btn = factory->createButton();
    diag = factory->createDialog();

    // Run!
    fmt::print("Button: {}\n", btn->getName());
    fmt::print("Dialog: {}\n", diag->getName());
  }
};