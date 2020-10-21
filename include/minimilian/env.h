#pragma once

#include "core.h"

namespace minimilian {

struct Env : public Processor {

  Env(Context &context) : Processor(context) {}

  /* Lots of people struggle with the envelope generators so here's a new easy
   one. It takes mental numbers for attack and release tho. Basically, they're
   exponentials. I'll map them out later so that it's a bit more intuitive */
  float ar(float input, float attack, float release, long holdtime,
           int trigger) {

    if (trigger == 1 && attackphase != 1 && holdphase != 1) {
      holdcount = 0;
      releasephase = 0;
      attackphase = 1;
    }

    if (attackphase == 1) {
      amplitude += (1 * attack);
      output = input * amplitude;
    }

    if (amplitude >= 1) {
      amplitude = 1;
      attackphase = 0;
      holdphase = 1;
    }

    if (holdcount < holdtime && holdphase == 1) {
      output = input;
      holdcount++;
    }

    if (holdcount == holdtime && trigger == 1) {
      output = input;
    }

    if (holdcount == holdtime && trigger != 1) {
      holdphase = 0;
      releasephase = 1;
    }

    if (releasephase == 1 && amplitude > 0.f) {
      output = input * (amplitude *= release);
    }

    return output;
  }

  /* adsr. It's not bad, very simple to use*/

  float adsr(float input, float attack, float decay, float sustain,
             float release, long holdtime, int trigger) {

    if (trigger == 1 && attackphase != 1 && holdphase != 1 && decayphase != 1) {
      holdcount = 0;
      decayphase = 0;
      sustainphase = 0;
      releasephase = 0;
      attackphase = 1;
    }

    if (attackphase == 1) {
      amplitude += (1 * attack);
      output = input * amplitude;
    }

    if (amplitude >= 1) {
      amplitude = 1;
      attackphase = 0;
      decayphase = 1;
    }

    if (decayphase == 1) {
      output = input * (amplitude *= decay);
      if (amplitude <= sustain) {
        decayphase = 0;
        holdphase = 1;
      }
    }

    if (holdcount < holdtime && holdphase == 1) {
      output = input * amplitude;
      holdcount++;
    }

    if (holdcount == holdtime && trigger == 1) {
      output = input * amplitude;
    }

    if (holdcount == holdtime && trigger != 1) {
      holdphase = 0;
      releasephase = 1;
    }

    if (releasephase == 1 && amplitude > 0.f) {
      output = input * (amplitude *= release);
    }

    return output;
  }

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
  inline float process(float input) {
    return env.ar(input, attack, release, holdtime, env.trigger);
  }

private:
  float attack = 1;
  float release = 0.9;
  long holdtime = 1;
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

  inline float process(float input) {
    return env.adsr(input, attack, decay, sustain, release, holdtime, env.trigger);
  }

private:
  float attack = 1;
  float decay = 0.99f;
  float sustain = 0.125f;
  float release = 0.9f;
  long holdtime = 1;
  Env env;
};

} // namespace minimilian
