#include <cmath>
#include "envelopefollower.h"

namespace minimilian {

EnvelopeFollower::EnvelopeFollower(Context &context) : Processor(context) {
  setAttack(100);
  setRelease(100);
  env = 0;
}

void EnvelopeFollower::setAttack(float attackMS) {
  attack =
      std::pow(0.01f, 1.0f / (attackMS * context.sampleRate * 0.001f));
}

void EnvelopeFollower::setRelease(float releaseMS) {
  release =
      std::pow(0.01f, 1.0f / (releaseMS * context.sampleRate * 0.001f));
}

float EnvelopeFollower::process(float input) {
  input = fabs(input);
  
  if (input > env)
    env = attack * (env - input) + input;
  else
    env = release * (env - input) + input;

  return env;
}

void EnvelopeFollower::reset() { env = 0; }

} // namespace minimilian