
#include "core.h"

#pragma once

namespace minimilian {

float linlin(float val, float inMin, float inMax, float outMin, float outMax) {
  return ((val - inMin) / (inMax - inMin) * (outMax - outMin)) + outMin;
}

float linexp(float val, float inMin, float inMax, float outMin, float outMax) {
  // clipping
  val = std::max(std::min(val, inMax), inMin);
  return std::pow((outMax / outMin), (val - inMin) / (inMax - inMin)) * outMin;
}

float explin(float val, float inMin, float inMax, float outMin, float outMax) {
  // clipping
  val = std::max(std::min(val, inMax), inMin);
  return (std::log(val / inMin) / std::log(inMax / inMin) * (outMax - outMin)) +
         outMin;
}

int clamp(int v, int low, int high) {
  v = std::min(high, v);
  v = std::max(low, v);
  return v;
}

} // namespace minimilian
