
#pragma once

#include "core.h"

namespace minimilian {

class Filter : public Processor {

public:
  Filter(Context &context);
  float cutoff;
  float resonance;
  float lores(float input, float cutoff1, float resonance);
  float hires(float input, float cutoff1, float resonance);
  float bandpass(float input, float cutoff1, float resonance);
  float lopass(float input, float cutoff);
  float hipass(float input, float cutoff);

private:
  float gain;
  float input;
  float output;
  float inputs[10];
  float outputs[10];
  float cutoff1;
  float x;  // speed
  float y;  // pos
  float z;  // pole
  float c;  // filter coefficient
};

struct LowPassReso : public Filter {
  LowPassReso(Context &context) : Filter(context) {}
  float process(float input, float cutoff, float resonance) {
    return lores(input, cutoff, resonance);
  }
};

struct HiPassReso : public Filter {
  HiPassReso(Context &context) : Filter(context) {}
  float process(float input, float cutoff, float resonance) {
    return hires(input, cutoff, resonance);
  }
};

struct Bandpass : public Filter {
  Bandpass(Context &context) : Filter(context) {}
  float process(float input, float cutoff, float resonance) {
    return bandpass(input, cutoff, resonance);
  }
};

struct LowPass : public Filter {
  LowPass(Context &context) : Filter(context) {}
  float process(float input, float cutoff) { return lopass(input, cutoff); }
};

struct HiPass : public Filter {
  HiPass(Context &context) : Filter(context) {}
  float process(float input, float cutoff) { return hipass(input, cutoff); }
};

} // namespace minimilian
