#pragma once

#include "core.h"

namespace maximilian {

class Envelope final : public Processor {

public:
  Envelope(Context &context);
  double line(int numberofsegments, double segments[100]);
  void trigger(int index, double amp);

private:
  double period;
  double output;
  double startval;
  double currentval;
  double nextval;
  int isPlaying;
  int valindex;
  double amplitude;
};

} // namespace maximilian
