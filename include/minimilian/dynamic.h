#pragma once

#include "core.h"

namespace minimilian {

class Dynamic : public Processor {

public:
  Dynamic(Context &context);

  float gate(float input, float threshold = 0.9f, long holdtime = 1,
             float attack = 1, float release = 0.9995f);

  float compressor(float input, float ratio, float threshold = 0.9f,
                   float attack = 1, float release = 0.9995f);

private:
  float input;
  float ratio;
  float currentRatio;
  float threshold;
  float output;
  float attack;
  float release;
  float amplitude;
  long holdtime;
  long holdcount;
  int attackphase, holdphase, releasephase;
};

class Compressor final : public Processor {
public:
  Compressor(Context &context) : Processor(context), dyn(context) {}

  void setRatio(float ratio) { this->ratio = ratio; }

  float getRatio() const { return ratio; }

  void setThreshold(float threshold) { this->threshold = threshold; }

  float getThreshold() const { return threshold; }

  void setAttack(float attack) { this->attack = attack; }

  float getAttack() const { return attack; }

  void setRelease(float release) { this->release = release; }

  float getRelease() const { return release; }

  float process(float input) {
    return dyn.compressor(input, ratio, threshold, attack, release);
  }

private:
  Dynamic dyn;
  float ratio = 4;
  float threshold = 0.9f;
  float attack = 1;
  float release = 0.9995f;
};

class Gate final : public Processor {
public:
  Gate(Context &context) : Processor(context), dyn(context) {}

  void setThreshold(float threshold) { this->threshold = threshold; }

  float getThreshold() const { return threshold; }

  void setHoldTime(long holdTime) { this->holdtime = holdTime; }

  long getHoldTime() const { return holdtime; }

  void setAttack(float attack) { this->attack = attack; }

  float getAttack() const { return attack; }

  void setRelease(float release) { this->release = release; }

  float getRelease() const { return release; }

  float process(float input, float threshold = 0.9f, long holdtime = 1,
                float attack = 1, float release = 0.9995f) {
    return dyn.gate(input, threshold, holdtime, attack, release);
  }

private:
  float threshold = 0.9f;
  long holdtime = 1;
  float attack = 1;
  float release = 0.9995f;
  Dynamic dyn;
};

} // namespace minimilian
