#pragma once

#include "core.h"
#include "delayline.h"
#include "filter.h"
#include "oscillator.h"

namespace minimilian {

class EnvelopeFollower final : public Processor {
public:
  EnvelopeFollower(Context &context) : Processor(context) {
    setAttack(100);
    setRelease(100);
    env = 0;
  }

  void setAttack(float attackMS) {
    attack = std::pow(0.01f, 1.0f / (attackMS * context.sampleRate * 0.001f));
  }

  void setRelease(float releaseMS) {
    release = std::pow(0.01f, 1.0f / (releaseMS * context.sampleRate * 0.001f));
  }

  float process(float input) {
    input = fabs(input);

    if (input > env)
      env = attack * (env - input) + input;
    else
      env = release * (env - input) + input;

    return env;
  }

  void reset() { env = 0; }

private:
  float attack, release, env;
};

} // namespace minimilian
