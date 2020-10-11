#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace minimilian {

const float TWOPI = 6.283185307179586476925286766559;

struct Context final {
  int sampleRate = 44100;
};

struct Processor {
  Processor(Context &context) : context(context) {}
  Context &context;
};

float mtof(int midinote);
} // namespace minimilian