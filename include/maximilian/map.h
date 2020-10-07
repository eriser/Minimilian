
#pragma once

namespace maximilian {

namespace Map {

double linlin(double val, double inMin, double inMax, double outMin,
              double outMax);

double linexp(double val, double inMin, double inMax, double outMin,
              double outMax);

double explin(double val, double inMin, double inMax, double outMin,
              double outMax);

int clamp(int v, const int low, const int high);
} // namespace Map

} // namespace maximilian
