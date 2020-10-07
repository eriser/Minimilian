#include <cmath>
#include "filter.h"

namespace maximilian {

Filter::Filter(Context &context)
    : Processor(context), x(0.0f), y(0.0f), z(0.0f), c(0.0f){};

// I particularly like these. cutoff between 0 and 1
float Filter::lopass(float input, float cutoff) {
  output = outputs[0] + cutoff * (input - outputs[0]);
  outputs[0] = output;

  return output;
}
// as above
float Filter::hipass(float input, float cutoff) {
  output = input - (outputs[0] + cutoff * (input - outputs[0]));
  outputs[0] = output;

  return output;
}
// awesome. cuttof is freq in hz. res is between 1 and whatever. Watch out!
float Filter::lores(float input, float cutoff1, float resonance) {
  auto sampleRate = context.sampleRate;

  cutoff = cutoff1;
  if (cutoff < 10)
    cutoff = 10;

  if (cutoff > sampleRate)
    cutoff = sampleRate;

  if (resonance < 1.)
    resonance = 1.;

  z = cos(TWOPI * cutoff / sampleRate);
  c = 2 - 2 * z;

  auto r = (std::sqrt(2.0f) * std::sqrt(-pow((z - 1.0f), 3.0f)) + resonance * (z - 1)) /
           (resonance * (z - 1));

  x = x + (input - y) * c;
  y = y + x;
  x = x * r;
  output = y;

  return output;
}

// working hires filter
float Filter::hires(float input, float cutoff1, float resonance) {
  auto sampleRate = context.sampleRate;

  cutoff = cutoff1;

  if (cutoff < 10)
    cutoff = 10;

  if (cutoff > (sampleRate))
    cutoff = (sampleRate);

  if (resonance < 1.)
    resonance = 1.;

  z = std::cos(TWOPI * cutoff / sampleRate);
  c = 2 - 2 * z;

  auto r = (std::sqrt(2.0f) * std::sqrt(-pow((z - 1.0f), 3.0f)) + resonance * (z - 1)) /
           (resonance * (z - 1));

  x = x + (input - y) * c;
  y = y + x;
  x = x * r;
  output = input - y;

  return output;
}

// This works a bit. Needs attention.
float Filter::bandpass(float input, float cutoff1, float resonance) {
  auto sampleRate = context.sampleRate;

  cutoff = cutoff1;

  if (cutoff > (sampleRate * 0.5f))
    cutoff = (sampleRate * 0.5f);

  if (resonance >= 1.)
    resonance = 0.999999f;

  z = std::cos(TWOPI * cutoff / sampleRate);

  inputs[0] = (1 - resonance) *
              (std::sqrt(resonance * (resonance - 4.0 * std::pow(z, 2.0f) + 2.0f) + 1));
  inputs[1] = 2 * z * resonance;
  inputs[2] = std::pow((resonance * -1), 2);

  output = inputs[0] * input + inputs[1] * outputs[1] + inputs[2] * outputs[2];
  outputs[2] = outputs[1];
  outputs[1] = output;

  return output;
}

} // namespace maximilian