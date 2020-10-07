
#pragma once

#include "core.h"
#include "delayline.h"
#include "oscillator.h"

namespace minimilian {

class Flanger final : public Processor {
public:
  Flanger(Context &context);

  // delay = delay time - ~800 sounds good
  // feedback = 0 - 1
  // speed = lfo speed in Hz, 0.0001 - 10 sounds good
  // depth = 0 - 1
  float process(float input, unsigned int delay, float feedback, float speed,
                float depth);

private:
  Delayline dl;
  Oscillator lfo;
};

} // namespace minimilian
