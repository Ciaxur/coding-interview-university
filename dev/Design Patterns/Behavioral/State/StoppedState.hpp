#pragma once
#include "State.hpp"
#include "PausedState.hpp"
#include "PlayState.hpp"

// CONCRETE CLASSES
class StopedState: protected State {
public:
  StopedState(Context *context): State(context) {};

  // Start Playing
  void play() {
    setIsPlay(true);
    ctx->changeState((State*) (new PlayState(ctx)));
  }

  // Pauses Increment and switches State
  void pause() {
    setIsPlay(false);
    ctx->changeState((State*) (new PausedState(ctx)));
  }

  // Do nothing...
  void stop() {}
};