#pragma once

namespace maximilian {

const double TWOPI = 6.283185307179586476925286766559;

struct Context final {
  int sampleRate = 44100;
  int channels = 2;
  int bufferSize = 1024;
};

struct Processor {
  Processor(Context &context) : context(context) {}
  Context &context;
};

double mtof(int midinote);

}