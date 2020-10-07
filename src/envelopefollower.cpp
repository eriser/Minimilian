#include <cmath>
#include "envelopefollower.h"

namespace maximilian {

EnvelopeFollower::EnvelopeFollower(Context &context) : Processor(context) {
  setAttack(100);
  setRelease(100);
  env = 0;
}

void EnvelopeFollower::setAttack(double attackMS) {
  attack =
      std::pow(0.01, 1.0 / (attackMS * context.sampleRate * 0.001));
}

void EnvelopeFollower::setRelease(double releaseMS) {
  release =
      std::pow(0.01, 1.0 / (releaseMS * context.sampleRate * 0.001));
}

double EnvelopeFollower::process(double input) {
  input = fabs(input);
  
  if (input > env)
    env = attack * (env - input) + input;
  else
    env = release * (env - input) + input;

  return env;
}

void EnvelopeFollower::reset() { env = 0; }

} // namespace maximilian