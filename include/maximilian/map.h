
#pragma once

namespace maximilian {

float linlin(float val, float inMin, float inMax, float outMin, float outMax);

float linexp(float val, float inMin, float inMax, float outMin, float outMax);

float explin(float val, float inMin, float inMax, float outMin, float outMax);

int clamp(int v, int low, int high);

} // namespace maximilian
