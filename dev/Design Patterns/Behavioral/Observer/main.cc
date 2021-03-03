#include <bits/stdc++.h>
#include "Observer.hpp"
using namespace std;

int main() {
  EventListener eventListener{};
  EventTypeInterface *intrEvent = new EventInterval(1);
  
  eventListener.subscribe(
    EventType::Interval,
    intrEvent
  );

  // eventListener.notify(EventType::Interval, "Yoyoyo");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  
  fmt::print("Cleaning Up...\n");
  delete intrEvent;
  return 0;
}
