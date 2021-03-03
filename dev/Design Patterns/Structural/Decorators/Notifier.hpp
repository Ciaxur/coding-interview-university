#include <fmt/format-inl.h>

class NotifierInterface {
public:
  virtual void notify() = 0;
};


// BASE CLASS FOR HOW NOTIFYING WORKS
class Notifier: public NotifierInterface {
public:
  void notify() {
    fmt::print("Base Notifier: Notify\n");
  };
};

class DiscordDecorator: public Notifier {
private:
  NotifierInterface *wrappee;

public:
  DiscordDecorator(NotifierInterface *notifier): wrappee(notifier) {}

  void notify() {
    fmt::print("Discord Wrapper: Notify\n");
    wrappee->notify();
  }  
};

class SlackDecorator: public Notifier {
private:
  NotifierInterface *wrapee;

public:
  SlackDecorator(NotifierInterface *notifier): wrapee(notifier) {}

  void notify() {
    fmt::print("Slack Wrapper: Notify\n");
    wrapee->notify();
  }  
};