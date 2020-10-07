#pragma once

#include "core.h"

namespace maximilian {

class Env : public Processor {

public:
  Env(Context &context);

  float ar(float input, float attack = 1, float release = 0.9,
           long holdtime = 1, int trigger = 0);
  float adsr(float input, float attack = 1, float decay = 0.99,
             float sustain = 0.125, float release = 0.9, long holdtime = 1,
             int trigger = 0);
  float input;
  float output;
  float attack;
  float decay;
  float sustain;
  float release;
  float amplitude;
  int trigger;
  long holdtime;
  long holdcount;
  int attackphase, decayphase, sustainphase, holdphase, releasephase;
};

struct AR final : public Env {
  AR(Context &context) : Env(context) {}

  float process(float input, float attack = 1, float release = 0.9,
                long holdtime = 1, int trigger = 0) {
    return ar(input, attack, release, holdtime, trigger);
  }
};

struct ADSR final : public Env {
  ADSR(Context &context) : Env(context) {}

  float process(float input, float attack = 1, float decay = 0.99,
                float sustain = 0.125, float release = 0.9, long holdtime = 1,
                int trigger = 0) {
    return adsr(input, attack, decay, sustain, release, holdtime, trigger);
  }
};

} // namespace maximilian
