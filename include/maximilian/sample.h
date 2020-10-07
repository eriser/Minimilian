
#pragma once

#include "core.h"
#include "lagexp.h"

namespace maximilian {

class Sample final : public Processor {

public:
  Sample(Context &context);
  ~Sample();

  void getLength();
  void setLength(unsigned long numSamples);

  bool load(const char* fileName, int channel = 0);

  bool loadOgg(const char* filename, int channel = 0);

  void trigger();

  void loopRecord(double newSample, bool recordEnabled,
                  double recordMix);

  void clear();

  void reset();

  double play();

  double playOnce();

  double playOnce(double speed);

  double play(double speed);

  double play(double frequency, double start, double end, double &pos);

  double play(double frequency, double start, double end);

  double play4(double frequency, double start, double end);

  double bufferPlay(unsigned char &bufferin, long length);

  double bufferPlay(unsigned char &bufferin, double speed, long length);

  double bufferPlay(unsigned char &bufferin, double frequency, double start,
                    double end);

  double bufferPlay4(unsigned char &bufferin, double frequency, double start,
                     double end);

  bool save(const char* filename);

private:
  int myChunkSize;
  int mySubChunk1Size;
  int readChannel;
  short myFormat;
  int myByteRate;
  short myBlockAlign;
  short myBitsPerSample;
  double position, recordPosition;
  double speed;
  double output;
  LagExp<double> loopRecordLag;
  int myDataSize;
  short myChannels;
  int mySampleRate;
  long length;
  char *myData;
  short *temp;
};

} // namespace maximilian
