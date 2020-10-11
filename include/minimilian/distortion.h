
#pragma once

namespace minimilian {

float fastatan(float x) { return (x / (1.0f + 0.28f * (x * x))); }

float atanDist(float in, float shape) {
  return (1.0f / std::atan(shape)) * std::atan(in * shape);
}

float fastAtanDist(float in, float shape) {
  return (1.0f / fastatan(shape)) * fastatan(in * shape);
}
} // namespace minimilian