
#pragma once

#include "core.h"
#include "delayline.h"
#include "oscillator.h"

namespace minimilian {

class Flanger final : public Processor {
public:
  Flanger(Context &context) : Processor(context), lfo(context) {}

  // delay = delay time - ~800 sounds good
  // feedback = 0 - 1
  // speed = lfo speed in Hz, 0.0001 - 10 sounds good
  // depth = 0 - 1
  float process(float input, unsigned int delay, float feedback, float speed,
                float depth) {
    auto lfoVal = lfo.triangle(speed);
    auto output =
        dl.process(input, delay + (lfoVal * depth * delay) + 1, feedback);
    auto normalise = (1 - std::fabs(output));
    output *= normalise;
    return (output + input) * 0.5f;
  }

private:
  Delayline dl;
  Oscillator lfo;
};

} // namespace minimilian
