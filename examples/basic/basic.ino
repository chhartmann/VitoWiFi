/*

This example defines three datapoints.
The first two are TEMPL type datapoints and have their own callback.
When no specific callback is attached to a datapoint, it uses the global callback.

Note the difference in return value between the callbacks:
for tempCallback uses value.getFloat() as TEMPL datapoints return a float.
globalCallback uses value.getString(char*,size_t). This method is independent of the returned type.

*/

#include <VitoWiFi.h>

VitoWiFi_setProtocol(P300);

DPTemp aussenTemp("temp-aussen", "temperature", 0x0800);
DPTemp boilerTemp("temp-brenner", "temperature", 0x0812);
DPUnsignedInt startsBrenner("starts-brenner", "burner", 0x088A);
DPHours laufzeitBrenner("laufzeit-brenner", "burner", 0x08A7);
DPByte statusStoerung("Status-stoerung", "status", 0x08A2);
DPErrHist stoerung1("stoerung-history1", "status", 0x7507);
DPTimeStamp systemzeit("Systemzeit", "status", 0x088E);
DPCycleTime timerMoHeizen("TimerMoHeizen", "timer-heating", 0x2000);

void tempCallbackHandler(const IDatapoint& dp, DPValue value) {
  Serial1.print(dp.getGroup());
  Serial1.print(" - ");
  Serial1.print(dp.getName());
  Serial1.print(": ");
  Serial1.println(value.getFloat(), 1);  // print with 1 decimal
}

void globalCallbackHandler(const IDatapoint& dp, DPValue value) {
  Serial1.print(dp.getGroup());
  Serial1.print(" - ");
  Serial1.print(dp.getName());
  Serial1.print(" is ");
  char value_str[128] = {0};
  value.getString(value_str, sizeof(value_str) - 1);
  Serial1.println(value_str);
}

void setup() {
  //  outsideTemp.setCallback(tempCallbackHandler);
  //  boilerTemp.setCallback(tempCallbackHandler);

  systemzeit.setWriteable(true);
  timerMoHeizen.setWriteable(true);

  VitoWiFi.setGlobalCallback(globalCallbackHandler);  // this callback will be used for all DPs without specific callback
                                                      // must be set after adding at least 1 datapoint
  VitoWiFi.setup(&Serial);
  Serial1.begin(115200);
  Serial1.println(F("Setup finished..."));
  VitoWiFi.setLogger(&Serial1);
  VitoWiFi.enableLogger();
}

void loop() {
  static unsigned long lastMillis = 0;

  cycletime_s ct;
  ct.cycle[0].from_hour = 10;
  ct.cycle[0].from_minute = 10;
  ct.cycle[0].till_hour = 11;
  ct.cycle[0].till_minute = 20;
  ct.cycle[1].from_hour = 12;
  ct.cycle[1].from_minute = 30;
  ct.cycle[1].till_hour = 13;
  ct.cycle[1].till_minute = 40;
  ct.cycle[2].from_hour = 14;
  ct.cycle[2].from_minute = 50;
  ct.cycle[2].till_hour = 15;
  ct.cycle[2].till_minute = 14;
  ct.cycle[3].from_hour = 16;
  ct.cycle[3].from_minute = 25;
  ct.cycle[3].till_hour = 16;
  ct.cycle[3].till_minute = 36;

  time_t rawtime = 1672904253;

  if (millis() - lastMillis > 30 * 1000UL) {  // read all values every 60 seconds
    lastMillis = millis();
    VitoWiFi.readAll();

    VitoWiFi.writeDatapoint(systemzeit, DPValue(rawtime));
    VitoWiFi.writeDatapoint(timerMoHeizen, DPValue(ct));
  }
  VitoWiFi.loop();
}
