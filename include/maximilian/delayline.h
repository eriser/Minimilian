
#pragma once

#include "core.h"

namespace maximilian {

class Delayline final : public Processor {

public:
  Delayline(Context &context);
  double dl(double input, int size, double feedback);
  double dl(double input, int size, double feedback, int position);

private:
  double frequency;
  int phase;
  double startphase;
  double endphase;
  double output;
  double memory[88200];
};

} // namespace maximilian