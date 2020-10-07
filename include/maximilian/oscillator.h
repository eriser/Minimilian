
#pragma once

#include "core.h"

namespace maximilian {

class Oscillator final : public Processor {

public:
  Oscillator(Context &context);
  double sinewave(double frequency);
  double coswave(double frequency);
  double phasor(double frequency);
  double phasor(double frequency, double startphase, double endphase);
  double saw(double frequency);
  double triangle(double frequency);
  double square(double frequency);
  double pulse(double frequency, double duty);
  double noise();
  double sinebuf(double frequency);
  double sinebuf4(double frequency);
  double sawn(double frequency);
  double rect(double frequency, double duty = 0.5);
  void phaseReset(double phaseIn);

private:
  double frequency;
  double phase;
  double startphase;
  double endphase;
  double output;
  double tri;
};

} // namespace maximilian
