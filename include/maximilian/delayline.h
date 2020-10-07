#pragma once

#include "core.h"

namespace maximilian {

class Delayline final : public Processor {

public:
  Delayline(Context &context);
  float process(float input, int size, float feedback);
  float process(float input, int size, float feedback, int position);

private:
  float frequency;
  int phase;
  float startphase;
  float endphase;
  float output;
  float memory[88200];
};

} // namespace maximilian
