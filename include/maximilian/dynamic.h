#pragma once

#include "core.h"

namespace maximilian {

class Dynamic : public Processor {

public:
  Dynamic(Context &context);

  float gate(float input, float threshold = 0.9f, long holdtime = 1,
             float attack = 1, float release = 0.9995f);

  float compressor(float input, float ratio, float threshold = 0.9f,
                   float attack = 1, float release = 0.9995f);

private:
  float input;
  float ratio;
  float currentRatio;
  float threshold;
  float output;
  float attack;
  float release;
  float amplitude;
  long holdtime;
  long holdcount;
  int attackphase, holdphase, releasephase;
};

struct Compressor final : public Dynamic {
  Compressor(Context &context) : Dynamic(context) {}

  float process(float input, float ratio, float threshold = 0.9f,
                float attack = 1, float release = 0.9995f) {
    return compressor(input, ratio, threshold, attack, release);
  }
};

struct Gate final : public Dynamic {
  Gate(Context &context) : Dynamic(context) {}

  float process(float input, float threshold = 0.9f, long holdtime = 1,
                float attack = 1, float release = 0.9995f) {
    return gate(input, threshold, holdtime, attack, release);
  }
};

} // namespace maximilian
