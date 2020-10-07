#include "distortion.h"
#include <cmath>

namespace maximilian {

namespace Distortion {

double fastatan(double x) { return (x / (1.0 + 0.28 * (x * x))); }

double atanDist(const double in, const double shape) {
  return (1.0 / std::atan(shape)) * std::atan(in * shape);
}

double fastAtanDist(const double in, const double shape) {
  return (1.0 / fastatan(shape)) * fastatan(in * shape);
}
} // namespace Distortion

} // namespace maximilian