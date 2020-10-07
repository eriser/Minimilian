#pragma once

#include "core.h"

namespace maximilian {

class Envelope final : public Processor {

public:
  Envelope(Context &context);
  float line(int numberofsegments, float segments[100]);
  void trigger(int index, float amp);

private:
  float period;
  float output;
  float startval;
  float currentval;
  float nextval;
  int isPlaying;
  int valindex;
  float amplitude;
};

} // namespace maximilian
