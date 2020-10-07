#pragma once

#include "core.h"

namespace maximilian {

class Dynamic : public Processor {

public:
  Dynamic(Context &context);

  double gate(double input, double threshold = 0.9, long holdtime = 1,
              double attack = 1, double release = 0.9995);

  double compressor(double input, double ratio, double threshold = 0.9,
                    double attack = 1, double release = 0.9995);

private:
  double input;
  double ratio;
  double currentRatio;
  double threshold;
  double output;
  double attack;
  double release;
  double amplitude;
  long holdtime;
  long holdcount;
  int attackphase, holdphase, releasephase;
};

struct Compressor final : public Dynamic {
  Compressor(Context &context) : Dynamic(context) {}

  double process(double input, double ratio, double threshold = 0.9,
                 double attack = 1, double release = 0.9995) {
    return compressor(input, ratio, threshold, attack, release);
  }
};

struct Gate final : public Dynamic {
  Gate(Context &context) : Dynamic(context) {}

  double process(double input, double threshold = 0.9, long holdtime = 1,
                 double attack = 1, double release = 0.9995) {
    return gate(input, threshold, holdtime, attack, release);
  }
};

} // namespace maximilian
