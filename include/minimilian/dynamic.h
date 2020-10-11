#pragma once

#include "core.h"

namespace minimilian {

class Dynamic : public Processor {

public:
  Dynamic(Context &context) : Processor(context) {}

  /* OK this compressor and gate are now ready to use. The envelopes, like all
   the envelopes in this recent update, use stupid algorithms for incrementing -
   consequently a long attack is something like 0.0001 and a long release is
   like 0.9999. Annoyingly, a short attack is 0.1, and a short release is 0.99.
   I'll sort this out laters */

  float gate(float input, float threshold, long holdtime, float attack,
             float release) {

    if (std::fabs(input) > threshold && attackphase != 1) {
      holdcount = 0;
      releasephase = 0;
      attackphase = 1;
      if (amplitude == 0)
        amplitude = 0.01f;
    }

    if (attackphase == 1 && amplitude < 1) {
      amplitude *= (1 + attack);
      output = input * amplitude;
    }

    if (amplitude >= 1) {
      attackphase = 0;
      holdphase = 1;
    }

    if (holdcount < holdtime && holdphase == 1) {
      output = input;
      holdcount++;
    }

    if (holdcount == holdtime) {
      holdphase = 0;
      releasephase = 1;
    }

    if (releasephase == 1 && amplitude > 0.) {
      output = input * (amplitude *= release);
    }

    return output;
  }

  float compressor(float input, float ratio, float threshold, float attack,
                   float release) {

    if (std::fabs(input) > threshold && attackphase != 1) {
      holdcount = 0;
      releasephase = 0;
      attackphase = 1;
      if (currentRatio == 0)
        currentRatio = ratio;
    }

    if (attackphase == 1 && currentRatio < ratio - 1) {
      currentRatio *= (1 + attack);
    }

    if (currentRatio >= ratio - 1) {
      attackphase = 0;
      releasephase = 1;
    }

    if (releasephase == 1 && currentRatio > 0.f) {
      currentRatio *= release;
    }

    if (input > 0.) {
      output = input / (1.f + currentRatio);
    } else {
      output = input / (1.f + currentRatio);
    }

    return output * (1 + log(ratio));
  }

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
