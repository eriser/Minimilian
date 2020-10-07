
#pragma once

#include "core.h"
#include "delayline.h"
#include "oscillator.h"

namespace maximilian {

class Flanger final : public Processor {
public:
  Flanger(Context &context);

  // delay = delay time - ~800 sounds good
  // feedback = 0 - 1
  // speed = lfo speed in Hz, 0.0001 - 10 sounds good
  // depth = 0 - 1
  double flange(double input, unsigned int delay,
                double feedback, double speed, double depth);

private:
  Delayline dl;
  Oscillator lfo;
};

} // namespace maximilian