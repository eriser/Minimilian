
#pragma once

#include "core.h"

namespace maximilian {

class Mix final : public Processor {

public:
  Mix(Context &context);

  float *stereo(float input, float two[2], float x);
  float *quad(float input, float four[4], float x, float y);
  float *ambisonic(float input, float eight[8], float x, float y, float z);

private:
  float x;
  float y;
  float z;
  float input;
  float two[2];
  float four[4];
  float eight[8];
};

} // namespace maximilian
