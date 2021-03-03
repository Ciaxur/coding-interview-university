/*
  Basically an Event Listener that the "client" (un)subscribes to
*/
#include <fmt/format-inl.h>
#include <unordered_map>
#include <vector>
#include <thread>
#include <chrono>

// FORWARD-DECLERATION
class EventListener;
enum EventType { Interval };


// EVENT TYPE INTERFACE
class EventTypeInterface {
public:
  virtual void update(void* context) = 0;
};

// CONCRETE EVENT TYPES
class EventInterval: public EventTypeInterface {
private:
  int interval_seconds;
  std::thread interval_thread;
  bool isRunning;
  
  static void notify(EventInterval *event, const char *msg) {
    while (event->isRunning) {
      std::this_thread::sleep_for(std::chrono::seconds(event->interval_seconds));
      event->update((void *)msg);
    }
    fmt::print("Thread Terminated\n");
  }
  
public:
  EventInterval(int seconds): interval_seconds(seconds), interval_thread{ this->notify, this, "YOYO" }, isRunning(true) {}
  ~EventInterval() {
    isRunning = false;
    fmt::print("Waiting on Thread to DIE\n");
    interval_thread.join();
  }

  void update(void* context) {
    // Expect Context to be of type String
    const char *msg = reinterpret_cast<const char*>(context);
    fmt::print("Interval Passed! {}\n", msg);
  }
};



// OBSERVER CLASS
class EventListener {
private:
  std::unordered_map<EventType, std::vector<EventTypeInterface*>> listeners;

public:
  EventListener() {};
  void subscribe(EventType eventType, EventTypeInterface *event) {
    try {
      listeners.at(eventType).push_back(event);
    } catch (...) {
      listeners.insert({ eventType, {}});
      listeners.at(eventType).push_back(event);
    }
  }

  void notify(EventType eventType, const char* message) {
    // Try and find subscribed event types
    try {
      for (auto e : listeners.at(eventType)) {
        e->update((void*)message);
      }
    } catch (std::out_of_range &e) {
      fmt::print("No Event Type '{}' Registered\n", eventType);
    }
  }

  void updateAll() {
    for (auto &p : listeners) {
      fmt::print("Notifying Events of type {}\n", p.first);
      for (int i = 0; i < p.second.size(); i++) {
        p.second[i]->update((void*)"Updating!");
      }
    }
  }

};