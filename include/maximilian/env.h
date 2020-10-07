
#pragma once

#include "core.h"

namespace maximilian {

class Env final : public Processor {

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

} // namespace maximilian
