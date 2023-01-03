/*

Copyright 2017 Bert Melis

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "DPTypes.hpp"

void convRaw::encode(uint8_t* out, DPValue in) {
  uint8_t tmp[MAX_DP_LENGTH] = {0};
  in.getRaw(tmp);
  memcpy(out, tmp, _length);
}
DPValue convRaw::decode(const uint8_t* in) {
  uint8_t tmp[MAX_DP_LENGTH] = {0};
  memcpy(tmp, in, _length);
  DPValue out(tmp, _length);
  return out;
}

void conv2_10_F::encode(uint8_t* out, DPValue in) {
  int16_t tmp = floor((in.getFloat() * 10) + 0.5);
  out[1] = tmp >> 8;
  out[0] = tmp & 0xFF;
}
DPValue conv2_10_F::decode(const uint8_t* in) {
  int16_t tmp = in[1] << 8 | in[0];
  DPValue out(tmp / 10.0f);
  return out;
}

void conv1_1_US::encode(uint8_t* out, DPValue in) {
  uint8_t tmp = in.getU8();
  out[0] = tmp;
}
DPValue conv1_1_US::decode(const uint8_t* in) {
  DPValue out(in[0]);
  return out;
}

void conv1_1_B::encode(uint8_t* out, DPValue in) { out[0] = in.getBool() ? 0x01 : 0x00; }
DPValue conv1_1_B::decode(const uint8_t* in) {
  DPValue out((*in) ? true : false);
  return out;
}

void conv4_1_UL::encode(uint8_t* out, DPValue in) {
  uint32_t tmp = in.getU32();
  out[3] = tmp >> 24;
  out[2] = tmp >> 16;
  out[1] = tmp >> 8;
  out[0] = tmp & 0xFF;
}

DPValue conv4_1_UL::decode(const uint8_t* in) {
  uint32_t tmp = in[3] << 24 | in[2] << 16 | in[1] << 8 | in[0];
  DPValue out(tmp);
  return out;
}

void conv2_1_UL::encode(uint8_t* out, DPValue in) {
  uint16_t tmp = in.getU16();
  out[1] = tmp >> 8;
  out[0] = tmp & 0xFF;
}
DPValue conv2_1_UL::decode(const uint8_t* in) {
  uint16_t tmp = in[1] << 8 | in[0];
  DPValue out(tmp);
  return out;
}

void conv4_3600_F::encode(uint8_t* out, DPValue in) {
  int32_t tmp = floor((in.getFloat() * 3600) + 0.5);
  out[3] = tmp >> 24;
  out[2] = tmp >> 16;
  out[1] = tmp >> 8;
  out[0] = tmp & 0xFF;
}
DPValue conv4_3600_F::decode(const uint8_t* in) {
  int32_t tmp = in[3] << 24 | in[2] << 16 | in[1] << 8 | in[0];
  DPValue out(tmp / 3600.0f);
  return out;
}

void conv1_10_F::encode(uint8_t* out, DPValue in) { out[0] = floor((in.getFloat() * 10) + 0.5); }
DPValue conv1_10_F::decode(const uint8_t* in) {
  DPValue out(in[0] / 10.0f);
  return out;
}

void conv2_1_US::encode(uint8_t* out, DPValue in) {
  uint16_t tmp = in.getU16();
  out[1] = tmp >> 8;
  out[0] = tmp & 0xFF;
}
DPValue conv2_1_US::decode(const uint8_t* in) {
  uint16_t tmp = in[1] << 8 | in[0];
  DPValue out(tmp);
  return out;
}

void conv8_1_Timer::encode(uint8_t* out, DPValue in) {
  uint64_t tmp = in.getU64();
  out[7] = tmp >> 56;
  out[6] = tmp >> 48;
  out[5] = tmp >> 40;
  out[4] = tmp >> 32;
  out[3] = tmp >> 24;
  out[2] = tmp >> 16;
  out[1] = tmp >> 8;
  out[0] = tmp & 0xFF;
}
DPValue conv8_1_Timer::decode(const uint8_t* in) {
  uint64_t tmp =
      ((uint64_t)in[7]) << 56 | ((uint64_t)in[6]) << 48 | ((uint64_t)in[5]) << 40 | ((uint64_t)in[4]) << 32 | ((uint64_t)in[3]) << 24 | ((uint64_t)in[2]) << 16 | ((uint64_t)in[1]) << 8 | in[0];
  DPValue out(tmp);
  return out;
}

void convTimeStamp::encode(uint8_t* out, DPValue in) {
  time_t t = in.getTimeStamp();
  struct tm* tmp = gmtime(&t);

  out[7] = tmp->tm_sec;
  out[6] = tmp->tm_min;
  out[5] = tmp->tm_hour;
  out[4] = tmp->tm_wday;
  out[3] = tmp->tm_mday;
  out[2] = tmp->tm_mon + 1;
  out[1] = (tmp->tm_year + 1900) % 100;
  out[0] = (u_int8_t)((tmp->tm_year + 1900) / 100);
}

DPValue convTimeStamp::decode(const uint8_t* in) {
  struct tm tmp;
  tmp.tm_isdst = -1;
  tmp.tm_hour = in[5];
  tmp.tm_min = in[6];
  tmp.tm_sec = in[7];
  tmp.tm_year = (uint32_t(in[0]) * 100 + uint32_t(in[1])) - 1900;
  tmp.tm_mon = in[2] - 1;
  tmp.tm_mday = in[3];
  time_t timeStamp = mktime(&tmp);
  DPValue out(timeStamp);
  return out;
}

void convErrHist::encode(uint8_t* out, DPValue in) {
  // not needed
}
DPValue convErrHist::decode(const uint8_t* in) {
  convTimeStamp tsConv;
  DPValue ts = tsConv.decode(in + 1);
  uint8_t errCode = in[0];
  DPValue out(errCode, ts.getTimeStamp());
  return out;
}
