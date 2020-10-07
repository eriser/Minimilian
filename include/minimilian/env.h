#pragma once

#include "core.h"

namespace minimilian {

struct Env : public Processor {
  Env(Context &context);
  float ar(float input, float attack = 1, float release = 0.9,
           long holdtime = 1, int trigger = 0);
  float adsr(float input, float attack = 1, float decay = 0.99,
             float sustain = 0.125, float release = 0.9, long holdtime = 1,
             int trigger = 0);
  float input;
  float output;
  float attack;
  float decay;
  float sustain;
  float release;
  float amplitude;
  int trigger;
  long holdtime;
  long holdcount;
  int attackphase, decayphase, sustainphase, holdphase, releasephase;
};

struct AR final : public Processor {
  inline AR(Context &context) : Processor(context), env(context) {}
  inline void setAttack(float attack) { this->attack = attack; }
  inline float getAttack() const { return attack; }
  inline void setRelease(float release) { this->release = release; }
  inline float getRelease() const { return release; }
  inline void setHoldTime(long holdTime) { this->holdtime = holdTime; }
  inline long getHoldTime() const { return holdtime; }
  inline void setTrigger(int trigger) { this->trigger = trigger; }
  inline int getTrigger() const { return trigger; }
  inline float process(float input) {
    return env.ar(input, attack, release, holdtime, trigger);
  }

private:
  float attack = 1;
  float release = 0.9;
  long holdtime = 1;
  int trigger = 0;
  Env env;
};

struct ADSR final : public Processor {
  inline ADSR(Context &context) : Processor(context), env(context) {}
  inline void setAttack(float attack) { this->attack = attack; }
  inline float getAttack() const { return attack; }
  inline void setDecay(float decay) { this->decay = decay; }
  inline float getDecay() const { return decay; }
  inline void setSustain(float sustain) { this->sustain = sustain; }
  inline float getSustain() const { return sustain; }
  inline void setRelease(float release) { this->release = release; }
  inline float getRelease() const { return release; }
  inline void setHoldTime(long holdTime) { this->holdtime = holdTime; }
  inline long getHoldTime() const { return holdtime; }
  inline void setTrigger(int trigger) { this->trigger = trigger; }
  inline int getTrigger() const { return trigger; }
  inline float process(float input) {
    return env.adsr(input, attack, decay, sustain, release, holdtime, trigger);
  }

private:
  float attack = 1;
  float decay = 0.99f;
  float sustain = 0.125f;
  float release = 0.9f;
  long holdtime = 1;
  int trigger = 0;
  Env env;
};

} // namespace minimilian
