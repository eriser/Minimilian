#include <cmath>
#include <algorithm>
#include "map.h"

namespace maximilian {

namespace Map {

double linlin(double val, double inMin, double inMax, double outMin,
                     double outMax) {
  return ((val - inMin) / (inMax - inMin) * (outMax - outMin)) + outMin;
}

double linexp(double val, double inMin, double inMax, double outMin,
                     double outMax) {
  // clipping
  val = std::max(std::min(val, inMax), inMin);
  return std::pow((outMax / outMin), (val - inMin) / (inMax - inMin)) * outMin;
}

double explin(double val, double inMin, double inMax, double outMin,
                     double outMax) {
  // clipping
  val = std::max(std::min(val, inMax), inMin);
  return (std::log(val / inMin) / std::log(inMax / inMin) * (outMax - outMin)) +
         outMin;
}

int clamp(int v, const int low, const int high) {
  v = std::min(high, v);
  v = std::max(low, v);
  return v;
}
}; // namespace Map

} // namespace maximilian