#pragma once

#include "core.h"
#include "delayline.h"
#include "filter.h"
#include "oscillator.h"

namespace minimilian {

class Chorus final : public Processor {
public:
  Chorus(Context &context)
      : Processor(context), lfo(context), lopass(context) {}

  // delay = delay time - ~800 sounds good
  void setDelay(unsigned int delay) { this->delay = delay; }
  unsigned int getDelay() const { return delay; }

  // feedback = 0 - 1
  void setFeedback(float feedback) { this->feedback = feedback; }
  float getFeedback() const { return feedback; }

  // speed = lfo speed in Hz, 0.0001 - 10 sounds good
  void setSpeed(float speed) { this->speed = speed; }
  float getSpeed() const { return speed; }

  // depth = 0 - 1
  void setDepth(float depth) { this->depth = depth; }
  float getDepth() const { return depth; }

  float process(float input) {

    auto lfoVal = lopass.lores(lfo.noise(), speed, 1.0f) * 2.0f;
    auto output1 =
        dl.process(input, delay + (lfoVal * depth * delay) + 1, feedback);
    auto output2 = dl2.process(
        input, (delay + (lfoVal * depth * delay * 1.02f) + 1) * 0.98f,
        feedback * 0.99f);
    output1 *= (1.0 - std::fabs(output1));
    output2 *= (1.0 - std::fabs(output2));

    return (output1 + output2 + input) / 3.0;
  }

private:
  Delayline dl, dl2;
  Oscillator lfo;
  Filter lopass;
  unsigned int delay = 800;
  float feedback = 0;
  float speed = 0.00001f;
  float depth = 0.5f;
};

} // namespace minimilian
