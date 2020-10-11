
#pragma once

#include "core.h"
#include "lagexp.h"

namespace minimilian {

class Sample final : public Processor {

public:
  Sample(Context &context);
  ~Sample();

  void getLength();
  void setLength(unsigned long numSamples);

  bool load(const char *fileName, int channel = 0);

  void trigger();

  void loopRecord(float newSample, bool recordEnabled, float recordMix);

  void clear();

  void reset();

  float play();

  float playOnce();

  float playOnce(float speed);

  float play(float speed);

  float play(float frequency, float start, float end, float &pos);

  float play(float frequency, float start, float end);

  float play4(float frequency, float start, float end);

  float bufferPlay(unsigned char &bufferin, long length);

  float bufferPlay(unsigned char &bufferin, float speed, long length);

  float bufferPlay(unsigned char &bufferin, float frequency, float start,
                   float end);

  float bufferPlay4(unsigned char &bufferin, float frequency, float start,
                    float end);

  bool save(const char *filename);

private:
  int myChunkSize;
  int mySubChunk1Size;
  int readChannel;
  short myFormat;
  int myByteRate;
  short myBlockAlign;
  short myBitsPerSample;
  float position, recordPosition;
  float speed;
  float output;
  LagExp<float> loopRecordLag;
  int myDataSize;
  short myChannels;
  int mySampleRate;
  long length;
  char *myData;
  short *temp;
};

} // namespace minimilian
