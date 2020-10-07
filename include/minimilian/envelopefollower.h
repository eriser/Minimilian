#pragma once

#include "core.h"
#include "delayline.h"
#include "filter.h"
#include "oscillator.h"

namespace minimilian {

class EnvelopeFollower final : public Processor {
public:
  EnvelopeFollower(Context &context);
  void setAttack(float attackMS);
  void setRelease(float releaseMS);
  float process(float input);
  void reset();

private:
  float attack, release, env;
};

} // namespace minimilian
