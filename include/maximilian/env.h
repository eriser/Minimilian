#pragma once

#include "core.h"

namespace maximilian {

class Env : public Processor {

public:
  Env(Context &context);

  double ar(double input, double attack = 1, double release = 0.9,
            long holdtime = 1, int trigger = 0);
  double adsr(double input, double attack = 1, double decay = 0.99,
              double sustain = 0.125, double release = 0.9, long holdtime = 1,
              int trigger = 0);
  double input;
  double output;
  double attack;
  double decay;
  double sustain;
  double release;
  double amplitude;
  int trigger;
  long holdtime;
  long holdcount;
  int attackphase, decayphase, sustainphase, holdphase, releasephase;
};

struct AR final : public Env
{
  AR(Context& context) : Env(context) {}

  double process(double input, double attack = 1, double release = 0.9,
                 long holdtime = 1, int trigger = 0) { return ar(input, attack, release, holdtime, trigger);}
};

struct ADSR final : public Env {
  ADSR(Context &context) : Env(context) {}

  double process(double input, double attack = 1, double decay = 0.99,
                 double sustain = 0.125, double release = 0.9,
                 long holdtime = 1, int trigger = 0) {
    return adsr(input, attack, decay, sustain, release, holdtime, trigger);
  }
};

} // namespace maximilian
