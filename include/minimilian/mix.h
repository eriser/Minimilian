
#pragma once

#include "core.h"

namespace minimilian {

class Mix final : public Processor {

public:
  Mix(Context &context) : Processor(context) {}

  // stereo bus
  float *stereo(float input, float two[2], float x) {
    if (x > 1)
      x = 1;
    if (x < 0)
      x = 0;
    two[0] = input * std::sqrt(1.0 - x);
    two[1] = input * std::sqrt(x);
    return (two);
  }

  // quad bus
  float *quad(float input, float four[4], float x, float y) {
    if (x > 1)
      x = 1;
    if (x < 0)
      x = 0;
    if (y > 1)
      y = 1;
    if (y < 0)
      y = 0;
    four[0] = input * std::sqrt((1.0 - x) * y);
    four[1] = input * std::sqrt((1.0 - x) * (1.0 - y));
    four[2] = input * std::sqrt(x * y);
    four[3] = input * std::sqrt(x * (1.0 - y));
    return (four);
  }

  // ambisonic bus
  float *ambisonic(float input, float eight[8], float x, float y, float z) {
    if (x > 1)
      x = 1;
    if (x < 0)
      x = 0;
    if (y > 1)
      y = 1;
    if (y < 0)
      y = 0;
    if (z > 1)
      y = 1;
    if (z < 0)
      y = 0;
    eight[0] = input * (std::sqrt((1.0 - x) * y) * 1.0 - z);
    eight[1] = input * (std::sqrt((1.0 - x) * (1.0 - y)) * 1.0 - z);
    eight[2] = input * (std::sqrt(x * y) * 1.0 - z);
    eight[3] = input * (std::sqrt(x * (1.0 - y)) * 1.0 - z);
    eight[4] = input * (std::sqrt((1.0 - x) * y) * z);
    eight[5] = input * (std::sqrt((1.0 - x) * (1.0 - y)) * z);
    eight[6] = input * std::sqrt((x * y) * z);
    eight[7] = input * std::sqrt((x * (1.0 - y)) * z);
    return (eight);
  }

private:
  float x;
  float y;
  float z;
  float input;
  float two[2];
  float four[4];
  float eight[8];
};

} // namespace minimilian
