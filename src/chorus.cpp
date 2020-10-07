#include <cmath>
#include "chorus.h"

namespace maximilian {

Chorus::Chorus(Context &context)
    : Processor(context), dl(context), dl2(context), lfo(context),
      lopass(context) {}

// delay = delay time - ~800 sounds good
// feedback = 0 - 1
// speed = lfo speed in Hz, 0.0001 - 10 sounds good
// depth = 0 - 1
double Chorus::chorus(double input, unsigned int delay,
                      double feedback, double speed,
                      double depth) {
  auto lfoVal = lopass.lores(lfo.noise(), speed, 1.0) * 2.0;
  auto output1 = dl.dl(input, delay + (lfoVal * depth * delay) + 1, feedback);
  auto output2 =
      dl2.dl(input, (delay + (lfoVal * depth * delay * 1.02) + 1) * 0.98,
             feedback * 0.99);
  output1 *= (1.0 - std::fabs(output1));
  output2 *= (1.0 - std::fabs(output2));

  return (output1 + output2 + input) / 3.0;
}

} // namespace maximilian