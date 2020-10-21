
#pragma once

#include "core.h"

namespace minimilian {

class Oscillator : public Processor {

public:
  Oscillator(Context &context) : Processor(context), phase(0.0) {}

  float noise() {
    // White Noise
    // always the same unless you seed it.
    float r = std::rand() / (float)RAND_MAX;
    output = r * 2 - 1;
    return (output);
  }

  void phaseReset(float phaseIn) {
    // This allows you to set the phase of the oscillator to anything you like.
    phase = phaseIn;
  }

  inline void phaseIncrement() {
    if (phase >= 1.0f)
      phase -= 1.0f;
    phase += (1.f / (context.sampleRate / frequency));
  } 

  float sinewave(float frequency) {
    output = sin(phase * TWOPI);
    phaseIncrement(); 
    return output;
  }

  float coswave(float frequency) {
    output = cos(phase * TWOPI);
    phaseIncrement();
    return output;
  }

  float phasor(float frequency) {
    output = phase;
    phaseIncrement(); 
    return output;
  }

  float square(float frequency) {
    output = phase < 0.5f ? -1.0f : 1.0f;
    phaseIncrement();
    return output;
  }

  float pulse(float frequency, float duty) {
    if (duty < 0.f)
      duty = 0;
    if (duty > 1.f)
      duty = 1;

    phaseIncrement();

    if (phase < duty)
      output = -1.f;
    if (phase > duty)
      output = 1.f;

    return output;
  }

  float phasor(float frequency, float startphase, float endphase) {
    // This is a phasor that takes a value for the start and end of the ramp.
    output = phase;
    if (phase < startphase) {
      phase = startphase;
    }
    if (phase >= endphase)
      phase = startphase;
    phase += ((endphase - startphase) / (context.sampleRate / frequency));
    return (output);
  }

  float saw(float frequency) { return phasor(frequency) * 2.0f - 1.0f; }

  float triangle(float frequency) {

    phaseIncrement();

    if (phase <= 0.5f) {
      output = (phase - 0.25f) * 4;
    } else {
      output = ((1.0f - phase) - 0.25f) * 4;
    }
    return (output);
  }

  float sinebuf(float frequency);
  float sinebuf4(float frequency);
  float sawn(float frequency);

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
  float process(float frequency, float duty) { return pulse(frequency, duty); }
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

} // namespace minimilian
