#include "sample.h"
#include <fstream>
#include <sstream>
#include <string>

namespace maximilian {

void Sample::loopRecord(float newSample, bool recordEnabled,
                        float recordMix) {
  loopRecordLag.addSample(recordEnabled);
  if (recordEnabled) {
    auto currentSample =
        ((short *)myData)[(unsigned long)recordPosition] / 32767.0;
    newSample = (recordMix * currentSample) + ((1.0 - recordMix) * newSample);
    newSample *= loopRecordLag.value();
    ((short *)myData)[(unsigned long)recordPosition] = newSample * 32767;
  }
  ++recordPosition;
  if (recordPosition == length)
    recordPosition = 0;
}

Sample::~Sample() {
  if (myData)
    free(myData);
  if (temp)
    free(temp);
}

Sample::Sample(Context &context)
    : Processor(context), myData(NULL), temp(NULL), position(0),
      recordPosition(0), myChannels(1),
      mySampleRate(context.sampleRate){};

// This sets the playback position to the start of a sample
void Sample::trigger() { position = 0; }

// This is the main read function.
bool Sample::load(const char *fileName, int channel) {
  bool result;
  readChannel = channel;

  std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
  result = inFile.is_open();
  if (inFile) {
    bool datafound = false;
    inFile.seekg(4, std::ios::beg);
    inFile.read((char *)&myChunkSize, 4); // read the ChunkSize

    inFile.seekg(16, std::ios::beg);
    inFile.read((char *)&mySubChunk1Size, 4); // read the SubChunk1Size

    // inFile.seekg(20, ios::beg);
    inFile.read(
        (char *)&myFormat,
        sizeof(short)); // read the file format.  This should be 1 for PCM

    // inFile.seekg(22, ios::beg);
    inFile.read((char *)&myChannels,
                sizeof(short)); // read the # of channels (1 or 2)

    // inFile.seekg(24, ios::beg);
    inFile.read((char *)&mySampleRate, sizeof(int)); // read the samplerate

    // inFile.seekg(28, ios::beg);
    inFile.read((char *)&myByteRate, sizeof(int)); // read the byterate

    // inFile.seekg(32, ios::beg);
    inFile.read((char *)&myBlockAlign, sizeof(short)); // read the blockalign

    // inFile.seekg(34, ios::beg);
    inFile.read((char *)&myBitsPerSample,
                sizeof(short)); // read the bitspersample

    // ignore any extra chunks
    char chunkID[5] = "";
    chunkID[4] = 0;
    int filePos = 20 + mySubChunk1Size;
    while (!datafound && !inFile.eof()) {
      inFile.seekg(filePos, std::ios::beg);
      inFile.read((char *)&chunkID, sizeof(char) * 4);
      inFile.seekg(filePos + 4, std::ios::beg);
      inFile.read((char *)&myDataSize,
                  sizeof(int)); // read the size of the data
      filePos += 8;
      if (strcmp(chunkID, "data") == 0) {
        datafound = true;
      } else {
        filePos += myDataSize;
      }
    }

    // read the data chunk
    myData = (char *)malloc(myDataSize * sizeof(char));
    inFile.seekg(filePos, std::ios::beg);
    inFile.read(myData, myDataSize);
    length = myDataSize * (0.5 / myChannels);
    inFile.close(); // close the input file

    if (myChannels > 1) {
      int position = 0;
      int channel = readChannel * 2;
      for (int i = channel; i < myDataSize + 6; i += (myChannels * 2)) {
        myData[position] = myData[i];
        myData[position + 1] = myData[i + 1];
        position += 2;
      }
    }
    temp = (short *)malloc(myDataSize * sizeof(char));
    memcpy(temp, myData, myDataSize * sizeof(char));

    free(myData);

  } else {
    //		cout << "ERROR: Could not load sample: " <<myPath << endl;
    ////This line seems to be hated by windows
    printf("ERROR: Could not load sample.");
  }

  return result; // this should probably be something more descriptive
}

// This plays back at the correct speed. Always loops.
float Sample::play() {
  position++;
  if ((long)position == length)
    position = 0;
  output = (float)temp[(long)position] / 32767.0;
  return output;
}

// This plays back at the correct speed. Only plays once. To retrigger, you have
// to manually reset the position
float Sample::playOnce() {
  position++;
  if ((long)position < length)
    output = (float)temp[(long)position] / 32767.0;
  else {
    output = 0;
  }
  return output;
}

// Same as above but takes a speed value specified as a ratio, with 1.0 as
// original speed
float Sample::playOnce(float speed) {
  position = position + (speed / (context.sampleRate / mySampleRate));
  float remainder = position - (long)position;
  if ((long)position < length)
    output = (float)((1 - remainder) * temp[1 + (long)position] +
                      remainder * temp[2 + (long)position]) /
             32767; // linear interpolation
  else
    output = 0;
  return (output);
}

// As above but looping
float Sample::play(float speed) {
  float remainder;
  long a, b;
  position = position + (speed / (context.sampleRate / mySampleRate));
  if (speed >= 0) {

    if ((long)position >= length - 1)
      position = 1;
    remainder = position - floor(position);
    if (position + 1 < length) {
      a = position + 1;

    } else {
      a = length - 1;
    }
    if (position + 2 < length) {
      b = position + 2;
    } else {
      b = length - 1;
    }

    output = (float)((1 - remainder) * temp[a] + remainder * temp[b]) /
             32767; // linear interpolation
  } else {
    if ((long)position < 0)
      position = length;
    remainder = position - floor(position);
    if (position - 1 >= 0) {
      a = position - 1;

    } else {
      a = 0;
    }
    if (position - 2 >= 0) {
      b = position - 2;
    } else {
      b = 0;
    }
    output = (float)((-1 - remainder) * temp[a] + remainder * temp[b]) /
             32767; // linear interpolation
  }
  return (output);
}

// placeholder
float Sample::play(float frequency, float start, float end) {
  return play(frequency, start, end, position);
}

// This allows you to say how often a second you want a specific chunk of audio
// to play
float Sample::play(float frequency, float start, float end, float &pos) {
  float remainder;
  if (end >= length)
    end = length - 1;
  long a, b;

  if (frequency > 0.) {
    if (pos < start) {
      pos = start;
    }

    if (pos >= end)
      pos = start;
    pos += ((end - start) / (context.sampleRate / frequency));
    remainder = pos - floor(pos);
    long posl = floor(pos);
    if (posl + 1 < length) {
      a = posl + 1;

    } else {
      a = posl - 1;
    }
    if (posl + 2 < length) {
      b = posl + 2;
    } else {
      b = length - 1;
    }

    output = (float)((1 - remainder) * temp[a] + remainder * temp[b]) /
             32767; // linear interpolation
  } else {
    frequency *= -1.;
    if (pos <= start)
      pos = end;
    pos -= ((end - start) / (context.sampleRate / frequency));
    remainder = pos - floor(pos);
    long posl = floor(pos);
    if (posl - 1 >= 0) {
      a = posl - 1;
    } else {
      a = 0;
    }
    if (posl - 2 >= 0) {
      b = posl - 2;
    } else {
      b = 0;
    }
    output = (float)((-1 - remainder) * temp[a] + remainder * temp[b]) /
             32767; // linear interpolation
  }

  return (output);
}

// Same as above. better cubic inerpolation. Cobbled together from various (pd
// externals, yehar, other places).
float Sample::play4(float frequency, float start, float end) {
  float remainder;
  float a, b, c, d, a1, a2, a3;
  if (frequency > 0.) {
    if (position < start) {
      position = start;
    }
    if (position >= end)
      position = start;
    position += ((end - start) / (context.sampleRate / frequency));
    remainder = position - floor(position);
    if (position > 0) {
      a = temp[(int)(floor(position)) - 1];

    } else {
      a = temp[0];
    }

    b = temp[(long)position];
    if (position < end - 2) {
      c = temp[(long)position + 1];

    } else {
      c = temp[0];
    }
    if (position < end - 3) {
      d = temp[(long)position + 2];

    } else {
      d = temp[0];
    }
    a1 = 0.5f * (c - a);
    a2 = a - 2.5 * b + 2.f * c - 0.5f * d;
    a3 = 0.5f * (d - a) + 1.5f * (b - c);
    output =
        (float)(((a3 * remainder + a2) * remainder + a1) * remainder + b) /
        32767;

  } else {
    frequency *= -1.;
    if (position <= start)
      position = end;
    position -= ((end - start) / (context.sampleRate / frequency));
    remainder = position - floor(position);
    if (position > start && position < end - 1) {
      a = temp[(long)position + 1];

    } else {
      a = temp[0];
    }

    b = temp[(long)position];
    if (position > start) {
      c = temp[(long)position - 1];

    } else {
      c = temp[0];
    }
    if (position > start + 1) {
      d = temp[(long)position - 2];

    } else {
      d = temp[0];
    }
    a1 = 0.5f * (c - a);
    a2 = a - 2.5 * b + 2.f * c - 0.5f * d;
    a3 = 0.5f * (d - a) + 1.5f * (b - c);
    output =
        (float)(((a3 * remainder + a2) * -remainder + a1) * -remainder + b) /
        32767;
  }

  return (output);
}

// You don't need to worry about this stuff.
float Sample::bufferPlay(unsigned char &bufferin, long length) {
  float remainder;
  short *buffer = (short *)&bufferin;
  position = (position + 1);
  remainder = position - (long)position;
  if ((long)position > length)
    position = 0;
  output = (float)((1 - remainder) * buffer[1 + (long)position] +
                    remainder * buffer[2 + (long)position]) /
           32767; // linear interpolation
  return (output);
}

float Sample::bufferPlay(unsigned char &bufferin, float speed, long length) {
  float remainder;
  long a, b;
  short *buffer = (short *)&bufferin;
  position = position + (speed / (context.sampleRate / mySampleRate));
  if (speed >= 0) {

    if ((long)position >= length - 1)
      position = 1;
    remainder = position - floor(position);
    if (position + 1 < length) {
      a = position + 1;

    } else {
      a = length - 1;
    }
    if (position + 2 < length) {
      b = position + 2;
    } else {
      b = length - 1;
    }

    output = (float)((1 - remainder) * buffer[a] + remainder * buffer[b]) /
             32767; // linear interpolation
  } else {
    if ((long)position < 0)
      position = length;
    remainder = position - floor(position);
    if (position - 1 >= 0) {
      a = position - 1;

    } else {
      a = 0;
    }
    if (position - 2 >= 0) {
      b = position - 2;
    } else {
      b = 0;
    }
    output = (float)((-1 - remainder) * buffer[a] + remainder * buffer[b]) /
             32767; // linear interpolation
  }
  return (output);
}

float Sample::bufferPlay(unsigned char &bufferin, float frequency,
                          float start, float end) {
  float remainder;
  length = end;
  long a, b;
  short *buffer = (short *)&bufferin;
  if (frequency > 0.) {
    if (position < start) {
      position = start;
    }

    if (position >= end)
      position = start;
    position += ((end - start) / (context.sampleRate / frequency));
    remainder = position - floor(position);
    long pos = floor(position);
    if (pos + 1 < length) {
      a = pos + 1;

    } else {
      a = pos - 1;
    }
    if (pos + 2 < length) {
      b = pos + 2;
    } else {
      b = length - 1;
    }

    output = (float)((1 - remainder) * buffer[a] + remainder * buffer[b]) /
             32767; // linear interpolation
  } else {
    frequency *= -1.;
    if (position <= start)
      position = end;
    position -= ((end - start) / (context.sampleRate / frequency));
    remainder = position - floor(position);
    long pos = floor(position);
    if (pos - 1 >= 0) {
      a = pos - 1;
    } else {
      a = 0;
    }
    if (pos - 2 >= 0) {
      b = pos - 2;
    } else {
      b = 0;
    }
    output = (float)((-1 - remainder) * buffer[a] + remainder * buffer[b]) /
             32767; // linear interpolation
  }

  return (output);
}

// better cubic inerpolation. Cobbled together from various (pd externals,
// yehar, other places).
float Sample::bufferPlay4(unsigned char &bufferin, float frequency,
                           float start, float end) {
  float remainder;
  float a, b, c, d, a1, a2, a3;
  short *buffer = (short *)&bufferin;
  if (frequency > 0.) {
    if (position < start) {
      position = start;
    }
    if (position >= end)
      position = start;
    position += ((end - start) / (context.sampleRate / frequency));
    remainder = position - floor(position);
    if (position > 0) {
      a = buffer[(int)(floor(position)) - 1];

    } else {
      a = buffer[0];
    }

    b = buffer[(long)position];
    if (position < end - 2) {
      c = buffer[(long)position + 1];

    } else {
      c = buffer[0];
    }
    if (position < end - 3) {
      d = buffer[(long)position + 2];

    } else {
      d = buffer[0];
    }
    a1 = 0.5f * (c - a);
    a2 = a - 2.5 * b + 2.f * c - 0.5f * d;
    a3 = 0.5f * (d - a) + 1.5f * (b - c);
    output =
        (float)(((a3 * remainder + a2) * remainder + a1) * remainder + b) /
        32767;

  } else {
    frequency *= -1.;
    if (position <= start)
      position = end;
    position -= ((end - start) / (context.sampleRate / frequency));
    remainder = position - floor(position);
    if (position > start && position < end - 1) {
      a = buffer[(long)position + 1];

    } else {
      a = buffer[0];
    }

    b = buffer[(long)position];
    if (position > start) {
      c = buffer[(long)position - 1];

    } else {
      c = buffer[0];
    }
    if (position > start + 1) {
      d = buffer[(long)position - 2];

    } else {
      d = buffer[0];
    }
    a1 = 0.5f * (c - a);
    a2 = a - 2.5 * b + 2.f * c - 0.5f * d;
    a3 = 0.5f * (d - a) + 1.5f * (b - c);
    output =
        (float)(((a3 * remainder + a2) * -remainder + a1) * -remainder + b) /
        32767;
  }

  return (output);
}

void Sample::getLength() { length = myDataSize * 0.5; }

void Sample::setLength(unsigned long numSamples) {

  short *newData = (short *)malloc(sizeof(short) * numSamples);
  if (NULL != temp) {
    unsigned long copyLength = std::min((unsigned long)length, numSamples);
    memcpy(newData, temp, sizeof(short) * copyLength);
  }
  temp = newData;
  myDataSize = numSamples * 2;
  length = numSamples;
  position = 0;
  recordPosition = 0;
}

void Sample::clear() { memset(myData, 0, myDataSize); }

void Sample::reset() { position = 0; }


bool Sample::save(const char* filename) {
  std::fstream myFile(filename, std::ios::out | std::ios::binary);

  // write the wav file per the wav file format
  myFile.seekp(0, std::ios::beg);
  myFile.write("RIFF", 4);
  myFile.write((char *)&myChunkSize, 4);
  myFile.write("WAVE", 4);
  myFile.write("fmt ", 4);
  myFile.write((char *)&mySubChunk1Size, 4);
  myFile.write((char *)&myFormat, 2);
  myFile.write((char *)&myChannels, 2);
  myFile.write((char *)&mySampleRate, 4);
  myFile.write((char *)&myByteRate, 4);
  myFile.write((char *)&myBlockAlign, 2);
  myFile.write((char *)&myBitsPerSample, 2);
  myFile.write("data", 4);
  myFile.write((char *)&myDataSize, 4);
  myFile.write(myData, myDataSize);

  return true;
}

} // namespace maximilian
