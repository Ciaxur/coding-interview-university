#pragma once
#include "State.hpp"
#include "PausedState.hpp"
#include "StoppedState.hpp"

// CONCRETE CLASSES
class PlayState: protected State {
public:
  PlayState(Context *context): State(context) {};

  // Does Nothing
  void play() {}

  // Pauses Increment and switches State
  void pause() {
    setIsPlay(false);
    ctx->changeState( (State*) (new PausedState(ctx)) );
  }

  // Pauses Increment, play, and switches State
  void stop() {
    setIsPlay(false);
    setAudioIncrement(0);
    ctx->changeState((State*) (new StopedState(ctx)));
  }
  
};


