
#pragma once

namespace minimilian {

float linlin(float val, float inMin, float inMax, float outMin, float outMax);

float linexp(float val, float inMin, float inMax, float outMin, float outMax);

float explin(float val, float inMin, float inMax, float outMin, float outMax);

int clamp(int v, int low, int high);

} // namespace minimilian
