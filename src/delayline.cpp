#include <memory.h>
#include "delayline.h"

namespace maximilian {

// Delay with feedback
Delayline::Delayline(Context &context) : Processor(context) {
  memset(memory, 0, 88200 * sizeof(float));
}

float Delayline::process(float input, int size, float feedback) {
  
  if (phase >= size) {
    phase = 0;
  }

  output = memory[phase];
  memory[phase] = (memory[phase] * feedback) + (input * feedback) * 0.5f;
  phase += 1;

  return output;
}

float Delayline::process(float input, int size, float feedback,
                          int position) {

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