

#pragma once

#include "core.h"
#include "delayline.h"
#include "filter.h"
#include "oscillator.h"

namespace maximilian {

class EnvelopeFollower : public Processor {
public:
  EnvelopeFollower(Context &context);
  void setAttack(double attackMS);
  void setRelease(double releaseMS);
  double play(double input);
  void reset();

private:
  double attack, release, env;
};

} // namespace maximilian
