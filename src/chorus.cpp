#include "chorus.h"
#include <cmath>

namespace minimilian {

Chorus::Chorus(Context &context)
    : Processor(context), lfo(context),
      lopass(context) {}

void Chorus::setDelay(unsigned int delay) { this->delay = delay; }
unsigned int Chorus::getDelay() const { return delay; }
void Chorus::setFeedback(float feedback) { this->feedback = feedback; }
float Chorus::getFeedback() const { return feedback; }
void Chorus::setSpeed(float speed) { this->speed = speed; }
float Chorus::getSpeed() const { return speed; }
void Chorus::setDepth(float depth) { this->depth = depth; }
float Chorus::getDepth() const { return depth; }

float Chorus::process(float input) {

  auto lfoVal = lopass.lores(lfo.noise(), speed, 1.0f) * 2.0f;
  auto output1 =
      dl.process(input, delay + (lfoVal * depth * delay) + 1, feedback);
  auto output2 =
      dl2.process(input, (delay + (lfoVal * depth * delay * 1.02f) + 1) * 0.98f,
                  feedback * 0.99f);
  output1 *= (1.0 - std::fabs(output1));
  output2 *= (1.0 - std::fabs(output2));

  return (output1 + output2 + input) / 3.0;
}

} // namespace minimilian