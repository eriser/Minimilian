
#pragma once

#include <cmath>

namespace maximilian {

const double TWOPI = 4 * std::acos(0.0);

struct Settings final {
  int sampleRate = 44100;
  int channels = 2;
  int bufferSize = 1024;
};

struct Context final {
  Settings settings;
};

struct Processor {
  Processor(Context &context) : context(context) {}
  Context &context;
};

double mtof(int midinote);

}