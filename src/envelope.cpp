
#include "envelope.h"

namespace minimilian {

Envelope::Envelope(Context &context) : Processor(context) {}

float Envelope::line(int numberofsegments, float segments[1000]) {
  // This is a basic multi-segment ramp generator that you can use for more or
  // less anything.
  // However, it's not that intuitive.
  if (isPlaying == 1) { // only make a sound once you've been triggered
    period = 4. / (segments[valindex + 1] * 0.0044f);
    nextval = segments[valindex + 2];
    currentval = segments[valindex];
    if (currentval - amplitude > 0.0000001f && valindex < numberofsegments) {
      amplitude +=
          ((currentval - startval) / (context.sampleRate / period));
    } else if (currentval - amplitude < -0.0000001f &&
               valindex < numberofsegments) {
      amplitude -= (((currentval - startval) * (-1)) /
                    (context.sampleRate / period));
    } else if (valindex > numberofsegments - 1) {
      valindex = numberofsegments - 2;
    } else {
      valindex = valindex + 2;
      startval = currentval;
    }
    output = amplitude;

  } else {
    output = 0;
  }

  return output;
}

// and this
void Envelope::trigger(int index, float amp) {
  isPlaying = 1; // ok the envelope is being used now.
  valindex = index;
  amplitude = amp;
}

} // namespace minimilian
