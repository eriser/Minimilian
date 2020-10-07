#pragma once

#include "core.h"
#include "delayline.h"
#include "filter.h"
#include "oscillator.h"

namespace minimilian {

class Chorus final : public Processor {
public:
  Chorus(Context &context);

  // delay = delay time - ~800 sounds good
  void setDelay(unsigned int delay);
  unsigned int getDelay() const;

  // feedback = 0 - 1
  void setFeedback(float feedback);
  float getFeedback() const;

  // speed = lfo speed in Hz, 0.0001 - 10 sounds good
  void setSpeed(float speed);
  float getSpeed() const;

  // depth = 0 - 1
  void setDepth(float depth);
  float getDepth() const;

  float process(float input);

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
