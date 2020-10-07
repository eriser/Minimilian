#include <memory.h>
#include "delayline.h"

namespace maximilian {

// Delay with feedback
Delayline::Delayline(Context &context) : Processor(context) {
  memset(memory, 0, 88200 * sizeof(double));
}

double Delayline::dl(double input, int size, double feedback) {
  
  if (phase >= size) {
    phase = 0;
  }

  output = memory[phase];
  memory[phase] = (memory[phase] * feedback) + (input * feedback) * 0.5;
  phase += 1;

  return output;
}

double Delayline::dl(double input, int size, double feedback, int position) {
  
  if (phase >= size)
    phase = 0;
 
  if (position >= size)
    position = 0;

  output = memory[position];
  memory[phase] = (memory[phase] * feedback) + (input * feedback);
  phase += 1;
  
  return output;
}

} // namespace maximilian