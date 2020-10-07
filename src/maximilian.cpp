
/*
 *  maximilian.cpp
 *  platform independent synthesis library using portaudio or rtaudio
 *
 *  Created by Mick Grierson on 29/12/2009.
 *  Copyright 2009 Mick Grierson & Strangeloop Limited. All rights reserved.
 *	Thanks to the Goldsmiths Creative Computing Team.
 *	Special thanks to Arturo Castro for the PortAudio implementation.
 *
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without
 *	restriction, including without limitation the rights to use,
 *	copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following
 *	conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *	OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "maximilian.h"

namespace maximilian {

// This is a lookup table for converting midi to frequency
const float mtofarray[129] = {0,
                               8.661957,
                               9.177024,
                               9.722718,
                               10.3,
                               10.913383,
                               11.562325,
                               12.25,
                               12.978271,
                               13.75,
                               14.567617,
                               15.433853,
                               16.351599,
                               17.323914,
                               18.354048,
                               19.445436,
                               20.601723,
                               21.826765,
                               23.124651,
                               24.5,
                               25.956543,
                               27.5,
                               29.135235,
                               30.867706,
                               32.703197,
                               34.647827,
                               36.708096,
                               38.890873,
                               41.203445,
                               43.65353,
                               46.249302,
                               49.,
                               51.913086,
                               55.,
                               58.27047,
                               61.735413,
                               65.406395,
                               69.295654,
                               73.416191,
                               77.781746,
                               82.406891,
                               87.30706,
                               92.498604,
                               97.998856,
                               103.826172,
                               110.,
                               116.540939,
                               123.470825,
                               130.81279,
                               138.591309,
                               146.832382,
                               155.563492,
                               164.813782,
                               174.61412,
                               184.997208,
                               195.997711,
                               207.652344,
                               220.,
                               233.081879,
                               246.94165,
                               261.62558,
                               277.182617,
                               293.664764,
                               311.126984,
                               329.627563,
                               349.228241,
                               369.994415,
                               391.995422,
                               415.304688,
                               440.,
                               466.163757,
                               493.883301,
                               523.25116,
                               554.365234,
                               587.329529,
                               622.253967,
                               659.255127,
                               698.456482,
                               739.988831,
                               783.990845,
                               830.609375,
                               880.,
                               932.327515,
                               987.766602,
                               1046.502319,
                               1108.730469,
                               1174.659058,
                               1244.507935,
                               1318.510254,
                               1396.912964,
                               1479.977661,
                               1567.981689,
                               1661.21875,
                               1760.,
                               1864.655029,
                               1975.533203,
                               2093.004639,
                               2217.460938,
                               2349.318115,
                               2489.015869,
                               2637.020508,
                               2793.825928,
                               2959.955322,
                               3135.963379,
                               3322.4375,
                               3520.,
                               3729.31,
                               3951.066406,
                               4186.009277,
                               4434.921875,
                               4698.63623,
                               4978.031738,
                               5274.041016,
                               5587.651855,
                               5919.910645,
                               6271.926758,
                               6644.875,
                               7040.,
                               7458.620117,
                               7902.132812,
                               8372.018555,
                               8869.84375,
                               9397.272461,
                               9956.063477,
                               10548.082031,
                               11175.303711,
                               11839.821289,
                               12543.853516,
                               13289.75};

float mtof(int midinote) {

  if (midinote < 0)
    return 0;

  if (midinote >= 128)
    return 13289.75;

  return mtofarray[midinote];
}

} // namespace maximilian