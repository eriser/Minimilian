
#pragma once

#include "core.h"

namespace maximilian {

class Oscillator : public Processor {

public:
  Oscillator(Context &context);
  double sinewave(double frequency);
  double coswave(double frequency);
  double phasor(double frequency);
  double phasor(double frequency, double startphase, double endphase);
  double saw(double frequency);
  double triangle(double frequency);
  double square(double frequency);
  double pulse(double frequency, double duty = 0.5);
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

struct Sine : public Oscillator {
  Sine(Context &context) : Oscillator(context) {}
  double process(double frequency) { return sinewave(frequency); }
};

struct Cosine : public Oscillator {
  Cosine(Context &context) : Oscillator(context) {}
  double process(double frequency) { return coswave(frequency); }
};

struct Phasor : public Oscillator {
  Phasor(Context &context) : Oscillator(context) {}
  double process(double frequency) { return phasor(frequency); }
  double process(double frequency, double startphase, double endphase) {
    return phasor(frequency, startphase, endphase);
  }
};

struct Saw : public Oscillator {
  Saw(Context &context) : Oscillator(context) {}
  double process(double frequency) { return saw(frequency); }
};

struct Triangle : public Oscillator {
  Triangle(Context &context) : Oscillator(context) {}
  double process(double frequency) { return triangle(frequency); }
};

struct Square : public Oscillator {
  Square(Context &context) : Oscillator(context) {}
  double process(double frequency) { return square(frequency); }
};

struct Pulse : public Oscillator {
  Pulse(Context &context) : Oscillator(context) {}
  double process(double frequency, double duty) {
    return pulse(frequency, duty);
  }
};

struct Noise : public Oscillator {
  Noise(Context &context) : Oscillator(context) {}
  double process() { return noise(); }
};

struct SineBuf : public Oscillator {
  SineBuf(Context &context) : Oscillator(context) {}
  double process(double frequency) { return sinebuf(frequency); }
};

struct SineBuf4 : public Oscillator {
  SineBuf4(Context &context) : Oscillator(context) {}
  double process(double frequency) { return sinebuf4(frequency); }
};

struct BLSaw : public Oscillator {
  BLSaw(Context &context) : Oscillator(context) {}
  double process(double frequency) { return sawn(frequency); }
};

struct Rect : public Oscillator {
  Rect(Context &context) : Oscillator(context) {}
  double process(double frequency, double duty = 0.5) {
    return rect(frequency, duty);
  }
};

} // namespace maximilian
