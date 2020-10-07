
#pragma once

#include "core.h"

namespace minimilian {

class Oscillator : public Processor {

public:
  Oscillator(Context &context);
  float sinewave(float frequency);
  float coswave(float frequency);
  float phasor(float frequency);
  float phasor(float frequency, float startphase, float endphase);
  float saw(float frequency);
  float triangle(float frequency);
  float square(float frequency);
  float pulse(float frequency, float duty = 0.5);
  float noise();
  float sinebuf(float frequency);
  float sinebuf4(float frequency);
  float sawn(float frequency);
  float rect(float frequency, float duty = 0.5);
  void phaseReset(float phaseIn);

private:
  float frequency;
  float phase;
  float startphase;
  float endphase;
  float output;
  float tri;
};

struct Sine : public Oscillator {
  Sine(Context &context) : Oscillator(context) {}
  float process(float frequency) { return sinewave(frequency); }
};

struct Cosine : public Oscillator {
  Cosine(Context &context) : Oscillator(context) {}
  float process(float frequency) { return coswave(frequency); }
};

struct Phasor : public Oscillator {
  Phasor(Context &context) : Oscillator(context) {}
  float process(float frequency) { return phasor(frequency); }
  float process(float frequency, float startphase, float endphase) {
    return phasor(frequency, startphase, endphase);
  }
};

struct Saw : public Oscillator {
  Saw(Context &context) : Oscillator(context) {}
  float process(float frequency) { return saw(frequency); }
};

struct Triangle : public Oscillator {
  Triangle(Context &context) : Oscillator(context) {}
  float process(float frequency) { return triangle(frequency); }
};

struct Square : public Oscillator {
  Square(Context &context) : Oscillator(context) {}
  float process(float frequency) { return square(frequency); }
};

struct Pulse : public Oscillator {
  Pulse(Context &context) : Oscillator(context) {}
  float process(float frequency, float duty) {
    return pulse(frequency, duty);
  }
};

struct Noise : public Oscillator {
  Noise(Context &context) : Oscillator(context) {}
  float process() { return noise(); }
};

struct SineBuf : public Oscillator {
  SineBuf(Context &context) : Oscillator(context) {}
  float process(float frequency) { return sinebuf(frequency); }
};

struct SineBuf4 : public Oscillator {
  SineBuf4(Context &context) : Oscillator(context) {}
  float process(float frequency) { return sinebuf4(frequency); }
};

struct BLSaw : public Oscillator {
  BLSaw(Context &context) : Oscillator(context) {}
  float process(float frequency) { return sawn(frequency); }
};

struct Rect : public Oscillator {
  Rect(Context &context) : Oscillator(context) {}
  float process(float frequency, float duty = 0.5) {
    return rect(frequency, duty);
  }
};

} // namespace minimilian
