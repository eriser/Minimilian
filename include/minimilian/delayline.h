#pragma once

#include <array>

namespace minimilian {

template <long maxSize> class DelaylineT final {

public:
  DelaylineT() { memory.fill(0); }

  float process(float input, int size, float feedback) {
    if (phase >= size) {
      phase = 0;
    }

    output = memory[phase];
    memory[phase] = (memory[phase] * feedback) + (input * feedback) * 0.5f;
    phase += 1;

    return output;
  }

  float process(float input, int size, float feedback, int position) {
    if (phase >= size)
      phase = 0;

    if (position >= size)
      position = 0;

    output = memory[position];
    memory[phase] = (memory[phase] * feedback) + (input * feedback);
    phase += 1;

    return output;
  }

private:
  float frequency;
  int phase;
  float startphase;
  float endphase;
  float output;
  std::array<float, maxSize> memory;
};

using Delayline = DelaylineT<88200>;

} // namespace minimilian
