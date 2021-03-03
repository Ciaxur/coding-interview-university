#pragma once
#include "Context.hpp"

// STATE INTERFACE
class State {
protected:
  Context *ctx;
  void setIsPlay(bool isPlay) { ctx->isPlay = isPlay; }
  void setAudioIncrement(int audioIncrement) { ctx->audioIncrement = audioIncrement; }

public:
  State(Context *context): ctx(context) {};
  virtual void play()   = 0;
  virtual void pause()  = 0;
  virtual void stop()   = 0;
};

