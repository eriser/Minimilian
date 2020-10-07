#include <cmath>
#include "flanger.h"

namespace maximilian {

Flanger::Flanger(Context &context)
    : Processor(context), dl(context), lfo(context) {}

// delay = delay time - ~800 sounds good
// feedback = 0 - 1
// speed = lfo speed in Hz, 0.0001 - 10 sounds good
// depth = 0 - 1
double Flanger::process(double input, unsigned int delay,
                       double feedback, double speed,
                       double depth) {
  auto lfoVal = lfo.triangle(speed);
  auto output = dl.process(input, delay + (lfoVal * depth * delay) + 1, feedback);
  auto normalise = (1 - std::fabs(output));
  output *= normalise;
  return (output + input) * 0.5;
}

} // namespace maximilian