
#pragma once

#include "core.h"

namespace maximilian {

class Filter : public Processor {

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

struct LowPassReso : public Filter {
  LowPassReso(Context &context) : Filter(context) {}
  double process(double input, double cutoff, double resonance) {
    return lores(input, cutoff, resonance);
  }
};

struct HiPassReso : public Filter {
  HiPassReso(Context &context) : Filter(context) {}
  double process(double input, double cutoff, double resonance) {
    return hires(input, cutoff, resonance);
  }
};

struct Bandpass : public Filter {
  Bandpass(Context &context) : Filter(context) {}
  double process(double input, double cutoff, double resonance) {
    return bandpass(input, cutoff, resonance);
  }
};

struct LowPass : public Filter {
  LowPass(Context &context) : Filter(context) {}
  double process(double input, double cutoff) { return lopass(input, cutoff); }
};

struct HiPass : public Filter {
  HiPass(Context &context) : Filter(context) {}
  double process(double input, double cutoff) { return hipass(input, cutoff); }
};

} // namespace maximilian
