
#pragma once

#include "core.h"
#include "delayline.h"
#include "oscillator.h"
#include "filter.h"

namespace maximilian {

class Chorus final : public Processor {
public:
  Chorus(Context &context);

  // delay = delay time - ~800 sounds good
  // feedback = 0 - 1
  // speed = lfo speed in Hz, 0.0001 - 10 sounds good
  // depth = 0 - 1
  double process(double input, unsigned int delay,
                double feedback, double speed, double depth);

private:
  Delayline dl, dl2;
  Oscillator lfo;
  Filter lopass;
};

} // namespace maximilian
