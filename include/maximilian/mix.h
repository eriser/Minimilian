
#pragma once

#include "core.h"

namespace maximilian {

class Mix final : public Processor {

public:
  Mix(Context &context);

  double *stereo(double input, double two[2], double x);
  double *quad(double input, double four[4], double x, double y);
  double *ambisonic(double input, double eight[8], double x, double y,
                    double z);

private:
  double x;
  double y;
  double z;
  double input;
  double two[2];
  double four[4];
  double eight[8];
};

} // namespace maximilian
