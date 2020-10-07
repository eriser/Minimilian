
#pragma once

#include "core.h"

namespace maximilian {

class Filter final : public Processor {

public:
  Filter(Context &context);
  double cutoff;
  double resonance;
  double lores(double input, double cutoff1, double resonance);
  double hires(double input, double cutoff1, double resonance);
  double bandpass(double input, double cutoff1, double resonance);
  double lopass(double input, double cutoff);
  double hipass(double input, double cutoff);

private:
  double gain;
  double input;
  double output;
  double inputs[10];
  double outputs[10];
  double cutoff1;
  double x; // speed
  double y; // pos
  double z; // pole
  double c; // filter coefficient
};

} // namespace maximilian
