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

#pragma once

// #include <stdint.h>
// #include <stdio.h>
// #include <memory>
// #include <algorithm>
#include <string.h>
#include <time.h>
#include "Constants.hpp"
#include "HardwareSerial.h"

enum DPValueType { BOOL, UINT8_T, UINT16_T, UINT32_T, UINT64_T, FLOAT, PTR, TIMESTAMP_T, ERR_HIST_T };

struct errCode2errStr_t {
  char code;
  const char* str;
};

const char errStr20[] PROGMEM = "Kurzschluss Vorlauftemperatursensor";
const char errStr10[] PROGMEM = "Kurzschluss Außentemperatursensor";
const char errStr21[] PROGMEM = "Kurzschluss Ruecklauftemperatursensor";
const char errStr18[] PROGMEM = "Unterbrechung Außentemperatursensor";
const char errStr28[] PROGMEM = "Unterbrechung Außentemperatursensor";
const char errStr29[] PROGMEM = "Unterbrechung Ruecklauftemperatursensor";
const char errStr30[] PROGMEM = "Kurzschluss Kesseltemperatursensor";
const char errStr38[] PROGMEM = "Unterbrechung Kesseltemperatursensor";
const char errStr0F[] PROGMEM = "Wartung (fuer Reset Codieradresse 24 auf 0 stellen)";
const char errStr40[] PROGMEM = "Kurzschluss Vorlauftemperatursensor M2";
const char errStr42[] PROGMEM = "Unterbrechung Vorlauftemperatursensor M2";
const char errStr50[] PROGMEM = "Kurzschluss Speichertemperatursensor";
const char errStr58[] PROGMEM = "Unterbrechung Speichertemperatursensor";
const char errStr92[] PROGMEM = "Solar: Kurzschluss Kollektortemperatursensor";
const char errStr93[] PROGMEM = "Solar: Kurzschluss Sensor S3";
const char errStr94[] PROGMEM = "Solar: Kurzschluss Speichertemperatursensor";
const char errStr9A[] PROGMEM = "Solar: Unterbrechung Kollektortemperatursensor";
const char errStr9B[] PROGMEM = "Solar: Unterbrechung Sensor S3";
const char errStr9C[] PROGMEM = "Solar: Unterbrechung Speichertemperatursensor";
const char errStr9F[] PROGMEM = "Solar: Fehlermeldung Solarteil (siehe Solarregler)";
const char errStrA7[] PROGMEM = "Bedienteil defekt";
const char errStrB0[] PROGMEM = "Kurzschluss Abgastemperatursensor";
const char errStrB1[] PROGMEM = "Kommunikationsfehler Bedieneinheit";
const char errStrB4[] PROGMEM = "Interner Fehler (Elektronik)";
const char errStrB5[] PROGMEM = "Interner Fehler (Elektronik)";
const char errStrB6[] PROGMEM = "Ungueltige Hardwarekennung (Elektronik)";
const char errStrB7[] PROGMEM = "Interner Fehler (Kesselkodierstecker)";
const char errStrB8[] PROGMEM = "Unterbrechung Abgastemperatursensor";
const char errStrB9[] PROGMEM = "Interner Fehler (Dateneingabe wiederholen)";
const char errStrBA[] PROGMEM = "Kommunikationsfehler Erweiterungssatz fuer Mischerkreis M2";
const char errStrBC[] PROGMEM = "Kommunikationsfehler Fernbedienung Vitorol, Heizkreis M1";
const char errStrBD[] PROGMEM = "Kommunikationsfehler Fernbedienung Vitorol, Heizkreis M2";
const char errStrBE[] PROGMEM = "Falsche Codierung Fernbedienung Vitorol";
const char errStrC1[] PROGMEM = "Externe Sicherheitseinrichtung (Kessel kuehlt aus)";
const char errStrC2[] PROGMEM = "Kommunikationsfehler Solarregelung";
const char errStrC5[] PROGMEM = "Kommunikationsfehler drehzahlgeregelte Heizkreispumpe, Heizkreis M1";
const char errStrC6[] PROGMEM = "Kommunikationsfehler drehzahlgeregelte Heizkreispumpe, Heizkreis M2";
const char errStrC7[] PROGMEM = "Falsche Codierung der Heizkreispumpe";
const char errStrC9[] PROGMEM = "Stoermeldeeingang am Schaltmodul-V aktiv";
const char errStrCD[] PROGMEM = "Kommunikationsfehler Vitocom 100 (KM-BUS)";
const char errStrCE[] PROGMEM = "Kommunikationsfehler Schaltmodul-V";
const char errStrCF[] PROGMEM = "Kommunikationsfehler LON Modul";
const char errStrD1[] PROGMEM = "Brennerstoerung";
const char errStrD4[] PROGMEM = "Sicherheitstemperaturbegrenzer hat ausgeloest oder Stoermeldemodul nicht richtig gesteckt";
const char errStrDA[] PROGMEM = "Kurzschluss Raumtemperatursensor, Heizkreis M1";
const char errStrDB[] PROGMEM = "Kurzschluss Raumtemperatursensor, Heizkreis M2";
const char errStrDD[] PROGMEM = "Unterbrechung Raumtemperatursensor, Heizkreis M1";
const char errStrDE[] PROGMEM = "Unterbrechung Raumtemperatursensor, Heizkreis M2";
const char errStrE4[] PROGMEM = "Fehler Versorgungsspannung";
const char errStrE5[] PROGMEM = "Interner Fehler (Ionisationselektrode)";
const char errStrE6[] PROGMEM = "Abgas- / Zuluftsystem verstopft";
const char errStrE9[] PROGMEM = "Ionisationsstrom waehrend des Kalibrierens nicht im gueltigen Bereich";
const char errStrF0[] PROGMEM = "Interner Fehler (Regelung tauschen)";
const char errStrF1[] PROGMEM = "Abgastemperaturbegrenzer ausgeloest";
const char errStrF2[] PROGMEM = "Temperaturbegrenzer ausgeloest";
const char errStrF3[] PROGMEM = "Flammensigal beim Brennerstart bereits vorhanden";
const char errStrF4[] PROGMEM = "Flammensigal nicht vorhanden";
const char errStrF7[] PROGMEM = "Differenzdrucksensor defekt";
const char errStrF8[] PROGMEM = "Brennstoffventil schließt zu spaet";
const char errStrF9[] PROGMEM = "Geblaesedrehzahl beim Brennerstart zu niedrig";
const char errStrFA[] PROGMEM = "Geblaesestillstand nicht erreicht";
const char errStrFD[] PROGMEM = "Fehler Gasfeurungsautomat";
const char errStrFE[] PROGMEM = "Starkes Stoerfeld (EMV) in der Naehe oder Elektronik defekt";
const char errStrFF[] PROGMEM = "Starkes Stoerfeld (EMV) in der Naehe oder interner Fehler";

const errCode2errStr_t errCode2errStr[] PROGMEM = {{0x20, errStr20}, {0x10, errStr10}, {0x21, errStr21}, {0x18, errStr18}, {0x28, errStr28}, {0x29, errStr29}, {0x30, errStr30}, {0x38, errStr38},
                                                   {0x0F, errStr0F}, {0x40, errStr40}, {0x42, errStr42}, {0x50, errStr50}, {0x58, errStr58}, {0x92, errStr92}, {0x93, errStr93}, {0x94, errStr94},
                                                   {0x9A, errStr9A}, {0x9B, errStr9B}, {0x9C, errStr9C}, {0x9F, errStr9F}, {0xA7, errStrA7}, {0xB0, errStrB0}, {0xB1, errStrB1}, {0xB4, errStrB4},
                                                   {0xB5, errStrB5}, {0xB6, errStrB6}, {0xB7, errStrB7}, {0xB8, errStrB8}, {0xB9, errStrB9}, {0xBA, errStrBA}, {0xBC, errStrBC}, {0xBD, errStrBD},
                                                   {0xBE, errStrBE}, {0xC1, errStrC1}, {0xC2, errStrC2}, {0xC5, errStrC5}, {0xC6, errStrC6}, {0xC7, errStrC7}, {0xC9, errStrC9}, {0xCD, errStrCD},
                                                   {0xCE, errStrCE}, {0xCF, errStrCF}, {0xD1, errStrD1}, {0xD4, errStrD4}, {0xDA, errStrDA}, {0xDB, errStrDB}, {0xDD, errStrDD}, {0xDE, errStrDE},
                                                   {0xE4, errStrE4}, {0xE5, errStrE5}, {0xE6, errStrE6}, {0xE9, errStrE9}, {0xF0, errStrF0}, {0xF1, errStrF1}, {0xF2, errStrF2}, {0xF3, errStrF3},
                                                   {0xF4, errStrF4}, {0xF7, errStrF7}, {0xF8, errStrF8}, {0xF9, errStrF9}, {0xFA, errStrFA}, {0xFD, errStrFD}, {0xFE, errStrFE}, {0xFF, errStrFF}};

// class which holds the returned or set value
class DPValue {
 private:
  union value {
    struct b_t {
      DPValueType type;
      bool value;
    } b;
    struct u8_t {
      DPValueType type;
      uint8_t value;
    } u8;
    struct u16_t {
      DPValueType type;
      uint16_t value;
    } u16;
    struct u32_t {
      DPValueType type;
      uint32_t value;
    } u32;
    struct u64_t {
      DPValueType type;
      uint64_t value;
    } u64;
    struct timestamp_t {
      DPValueType type;
      time_t timeStamp;
    } timestamp;

    struct errHist_t : timestamp_t {
      uint8_t errCode;
    } errHist;
    struct f_t {
      DPValueType type;
      float value;
    } f;
    struct raw {
      DPValueType type;
      uint8_t value[MAX_DP_LENGTH];
      size_t length;
    } raw;
    // value() : u32{PTR, 0} {}
    value(bool b) : b{BOOL, b} {}
    value(uint8_t u8) : u8{UINT8_T, u8} {}
    value(uint16_t u16) : u16{UINT16_T, u16} {}
    value(uint32_t u32) : u32{UINT32_T, u32} {}
    value(uint64_t u64) : u64{UINT64_T, u64} {}
    value(time_t t) : timestamp{TIMESTAMP_T, t} {}
    value(uint8_t u8, time_t t) : errHist{ERR_HIST_T, t, u8} {}
    value(float f) : f{FLOAT, f} {}
    value(uint8_t* r, size_t length) : raw{PTR, {0}, length} {
      if (length <= MAX_DP_LENGTH)
        memcpy(raw.value, r, length);
      else
        memcpy(raw.value, r, MAX_DP_LENGTH);
    }
  } v;

 public:
  // DPValue() : v() {}
  explicit DPValue(bool b) : v(b) {}
  explicit DPValue(uint8_t u8) : v(u8) {}
  explicit DPValue(uint16_t u16) : v(u16) {}
  explicit DPValue(uint32_t u32) : v(u32) {}
  explicit DPValue(uint64_t u64) : v(u64) {}
  explicit DPValue(time_t t) : v(t) {}
  explicit DPValue(uint8_t u8, time_t u64) : v(u8, u64) {}
  explicit DPValue(float f) : v(f) {}
  DPValue(uint8_t* r, size_t length) : v(r, length) {}
  DPValue(DPValue const&) = default;
  ~DPValue() = default;
  bool getBool() {
    if (v.b.type == BOOL) {
      return v.b.value;
    } else {
      return false;
    }
  }
  uint8_t getU8() {
    if (v.b.type == UINT8_T) {
      return v.u8.value;
    } else {
      return 0;
    }
  }
  uint16_t getU16() {
    if (v.b.type == UINT16_T) {
      return v.u16.value;
    } else {
      return 0;
    }
  }
  uint32_t getU32() {
    if (v.b.type == UINT32_T) {
      return v.u32.value;
    } else {
      return 0;
    }
  }
  uint64_t getU64() {
    if (v.b.type == UINT64_T) {
      return v.u64.value;
    } else {
      return 0;
    }
  }
  float getFloat() {
    if (v.b.type == FLOAT) {
      return v.f.value;
    } else {
      return 0.0;
    }
  }
  time_t getTimeStamp() {
    if (v.b.type == ERR_HIST_T || v.b.type == TIMESTAMP_T) {
      return v.timestamp.timeStamp;
    } else
      return 0;
  }
  void getRaw(uint8_t* out) { memcpy(out, &v.raw.value[0], v.raw.length); }
  size_t getRawLength() { return v.raw.length; }
  void getString(char* c, size_t s) {
    switch (v.b.type) {
      case BOOL:
        snprintf(c, s, "%s", (v.b.value) ? "true" : "false");
        break;
      case UINT8_T:
        snprintf(c, s, "%u", v.u8.value);
        break;
      case UINT16_T:
        snprintf(c, s, "%u", v.u16.value);
        break;
      case UINT32_T:
        snprintf(c, s, "%u", v.u32.value);
        break;
      case UINT64_T:
        snprintf(c, s, "%llu", v.u64.value);
        break;
      case FLOAT:
        snprintf(c, s, "%.1f", v.f.value);
        break;
      case PTR:
        for (uint8_t i = 0; i < v.raw.length; ++i) {
          snprintf(c, s - 2 * i, "%02x", v.raw.value[i]);
          c += 2;
        }
        break;
      case TIMESTAMP_T: {
        struct tm* tms = gmtime(&v.timestamp.timeStamp);
        strftime(c, s, "%d.%m.%Y %H:%M:%S", tms);
      } break;
      case ERR_HIST_T: {
        struct tm* tms = gmtime(&v.errHist.timeStamp);
        char ts[20] = {0};
        strftime(ts, sizeof(ts), "%d.%m.%Y %H:%M:%S", tms);
        size_t index = snprintf(c, s, "%s Fehler %02x ", ts, v.errHist.errCode);

        for (uint32_t i = 0; i < sizeof(errCode2errStr) / sizeof(errCode2errStr[0]); ++i) {
          errCode2errStr_t tmp;
          memcpy_P(&tmp, &errCode2errStr[i], sizeof(errCode2errStr_t));
          if (tmp.code == v.errHist.errCode) {
            strncat_P(c + index, tmp.str, s - index);
            break;
          }
        }
      } break;
    }
  }
};
