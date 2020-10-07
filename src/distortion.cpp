#include "distortion.h"
#include <cmath>

namespace maximilian {

double fastatan(double x) { return (x / (1.0 + 0.28 * (x * x))); }

double atanDist(double in, double shape) {
  return (1.0 / std::atan(shape)) * std::atan(in * shape);
}

double fastAtanDist(double in, double shape) {
  return (1.0 / fastatan(shape)) * fastatan(in * shape);
}

} // namespace maximilian