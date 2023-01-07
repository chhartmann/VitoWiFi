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
  uint32 year = tmp->tm_year + 1900;
  uint8_t year4 = (uint8_t)(year / 1000);
  uint8_t year3 = (uint8_t)((year - year4 * 1000) / 100);
  uint8_t year2 = (uint8_t)((year - year4 * 1000 - year3 * 100) / 10);
  uint8_t year1 = year % 10;
  out[7] = (uint8_t(tmp->tm_sec / 10) << 4) | (tmp->tm_sec % 10);
  out[6] = (uint8_t(tmp->tm_min / 10) << 4) | (tmp->tm_min % 10);
  out[5] = (uint8_t(tmp->tm_hour / 10) << 4) | (tmp->tm_hour % 10);
  out[4] = tmp->tm_wday;
  out[3] = (uint8_t(tmp->tm_mday / 10) << 4) | (tmp->tm_mday % 10);
  out[2] = (uint8_t((tmp->tm_mon + 1) / 10) << 4) | ((tmp->tm_mon + 1) % 10);
  out[1] = (year2 << 4) | year1;
  out[0] = (year4 << 4) | year3;
}

DPValue convTimeStamp::decode(const uint8_t* in) {
  struct tm tmp;
  tmp.tm_isdst = -1;
  tmp.tm_hour = (in[5] >> 4) * 10 + (in[5] & 0x0F);
  tmp.tm_min = (in[6] >> 4) * 10 + (in[6] & 0x0F);
  tmp.tm_sec = (in[7] >> 4) * 10 + (in[7] & 0x0F);
  tmp.tm_year = (in[0] >> 4) * 1000 + (in[0] & 0x0F) * 100 + (in[1] >> 4) * 10 + (in[1] & 0x0F) - 1900;
  tmp.tm_mon = (in[2] >> 4) * 10 + (in[2] & 0x0F) - 1;
  tmp.tm_mday = (in[3] >> 4) * 10 + (in[3] & 0x0F);
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

void convCycleTime::encode(uint8_t* out, DPValue in) {
  const cycletime_s* ct = in.getCycletime();
  for (uint32_t i = 0; i < 4; ++i) {
    if (ct->cycle[i].from_hour == 0xff || ct->cycle[i].from_minute == 0xff) {
      out[i * 2] = 0xff;
    } else {
      out[i * 2] = (ct->cycle[i].from_hour << 3) | (ct->cycle[i].from_minute / 10);
    }
    if (ct->cycle[i].till_hour == 0xff || ct->cycle[i].till_minute == 0xff) {
      out[i * 2 + 1] = 0xff;
    } else {
      out[i * 2 + 1] = (ct->cycle[i].till_hour << 3) | (ct->cycle[i].till_minute / 10);
    }
  }
}

DPValue convCycleTime::decode(const uint8_t* in) {
  cycletime_s ct;
  for (uint32_t i = 0; i < 4; ++i) {
    uint8_t from = in[i * 2];
    uint8_t till = in[i * 2 + 1];
    if (from == 0xff) {
      ct.cycle[i].from_hour = 0xff;
      ct.cycle[i].from_minute = 0xff;
    } else {
      ct.cycle[i].from_hour = (from & 0xf8) >> 3;
      ct.cycle[i].from_minute = (from & 7) * 10;
    }
    if (till == 0xff) {
      ct.cycle[i].till_hour = 0xff;
      ct.cycle[i].till_minute = 0xff;
    } else {
      ct.cycle[i].till_hour = (till & 0xf8) >> 3;
      ct.cycle[i].till_minute = (till & 7) * 10;
    }
  }
  DPValue out(ct);
  return out;
}
