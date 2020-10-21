#pragma once

#include "core.h"
#include <vector>

namespace minimilian {

class Envelope final : public Processor {

public:
  Envelope(Context &context) : Processor(context) {}

  float line(int numberofsegments, const std::vector<double> &segments) {
    // This is a basic multi-segment ramp generator that you can use for more or
    // less anything.
    // However, it's not that intuitive.
    if (isPlaying == 1) { // only make a sound once you've been triggered
      period = 4. / (segments[valindex + 1] * 0.0044f);
      nextval = segments[valindex + 2];
      currentval = segments[valindex];
      if (currentval - amplitude > 0.0000001f && valindex < numberofsegments) {
        amplitude += ((currentval - startval) / (context.sampleRate / period));
      } else if (currentval - amplitude < -0.0000001f &&
                 valindex < numberofsegments) {
        amplitude -=
            (((currentval - startval) * (-1)) / (context.sampleRate / period));
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

  void trigger(int index, float amp) {
    isPlaying = 1; // ok the envelope is being used now.
    valindex = index;
    amplitude = amp;
  }

  void setValIndex(int index) { valindex = index; }
  int getValIndex() const { return valindex; }

  void setAmplitude(float amp) { amplitude = amp; }
  float getAmplitude() const { return amplitude; }

private:
  float period;
  float output;
  float startval;
  float currentval;
  float nextval;
  int isPlaying;
  int valindex;
  float amplitude;
};

} // namespace minimilian
