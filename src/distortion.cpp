#include "distortion.h"
#include <cmath>

namespace maximilian {

float fastatan(float x) { return (x / (1.0 + 0.28 * (x * x))); }

float atanDist(float in, float shape) {
  return (1.0 / std::atan(shape)) * std::atan(in * shape);
}

float fastAtanDist(float in, float shape) {
  return (1.0 / fastatan(shape)) * fastatan(in * shape);
}

} // namespace maximilian