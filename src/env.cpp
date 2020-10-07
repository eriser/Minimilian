#include "env.h"

namespace maximilian {

Env::Env(Context &context) : Processor(context) {}

/* Lots of people struggle with the envelope generators so here's a new easy
 one. It takes mental numbers for attack and release tho. Basically, they're
 exponentials. I'll map them out later so that it's a bit more intuitive */
float Env::ar(float input, float attack, float release, long holdtime,
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

  if (releasephase == 1 && amplitude > 0.) {
    output = input * (amplitude *= release);
  }

  return output;
}

/* adsr. It's not bad, very simple to use*/

float Env::adsr(float input, float attack, float decay, float sustain,
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

  if (releasephase == 1 && amplitude > 0.) {
    output = input * (amplitude *= release);
  }

  return output;
}

} // namespace maximilian