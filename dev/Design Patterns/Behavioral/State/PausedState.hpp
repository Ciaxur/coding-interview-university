#pragma once
#include "State.hpp"
#include "PlayState.hpp"
#include "StoppedState.hpp"

// CONCRETE CLASSES
class PausedState: protected State {
public:
  PausedState(Context *context): State(context) {};

  // Start Playing
  void play() {
    setIsPlay(true);
    ctx->changeState((State*) (new PlayState(ctx)));
  }

  // Do nothing...
  void pause() {}

  // Pauses Increment, play, and switches State
  void stop() {
    setIsPlay(false);
    setAudioIncrement(0);
    ctx->changeState((State*) (new StopedState(ctx)));
  }
};
