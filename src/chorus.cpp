#include "chorus.h"

namespace maximilian {

Chorus::Chorus(Context &context)
    : Processor(context), dl(context), dl2(context), lfo(context),
      lopass(context) {}

// delay = delay time - ~800 sounds good
// feedback = 0 - 1
// speed = lfo speed in Hz, 0.0001 - 10 sounds good
// depth = 0 - 1
double Chorus::chorus(const double input, const unsigned int delay,
                      const double feedback, const double speed,
                      const double depth) {
  double output1, output2;
  double lfoVal = lfo.noise();
  lfoVal = lopass.lores(lfoVal, speed, 1.0) * 2.0;
  output1 = dl.dl(input, delay + (lfoVal * depth * delay) + 1, feedback);
  output2 = dl2.dl(input, (delay + (lfoVal * depth * delay * 1.02) + 1) * 0.98,
                   feedback * 0.99);
  output1 *= (1.0 - fabs(output1));
  output2 *= (1.0 - fabs(output2));
  return (output1 + output2 + input) / 3.0;
}

} // namespace maximilian