#include "flanger.h"

namespace maximilian {

Flanger::Flanger(Context &context)
    : Processor(context), dl(context), lfo(context) {}

// delay = delay time - ~800 sounds good
// feedback = 0 - 1
// speed = lfo speed in Hz, 0.0001 - 10 sounds good
// depth = 0 - 1
double Flanger::flange(const double input, const unsigned int delay,
                       const double feedback, const double speed,
                       const double depth) {
  double lfoVal = lfo.triangle(speed);
  double output = dl.dl(input, delay + (lfoVal * depth * delay) + 1, feedback);
  double normalise = (1 - fabs(output));
  output *= normalise;
  return (output + input) / 2.0;
}

} // namespace maximilian