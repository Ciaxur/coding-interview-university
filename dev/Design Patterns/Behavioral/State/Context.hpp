#pragma once
#include <memory>
#include "State.hpp"
class State;

// CONTEXT CLASS (Intermediary or State Holder/Manager)
class Context {
private:
  std::unique_ptr<State> state;

protected:
  friend class State;
  bool isPlay         = false;
  int audioIncrement  = 0;
  
public:
  void changeState(State *newState) { state = std::unique_ptr<State>{newState}; }

  void run() {}
  
  // Actions that change the state
  void play() { state.get()->play(); }
  void pause() { state.get()->pause(); }
  void stop() { state.get()->stop(); }
};