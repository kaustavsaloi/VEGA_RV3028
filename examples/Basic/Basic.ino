#include <VEGA_RV3028.h>

TwoWire myWire = TwoWire(1);
VEGA_RV3028 rtc(myWire);

void setup() {
  Serial.begin(115200);

  if (!rtc.begin()) {
    Serial.println("RTC not detected!");
    while (1);
  }

  VEGA_RV3028::Time t = {0, 30, 12, 2, 2, 4, 25};
  rtc.setTime(t);
}

void loop() {
  VEGA_RV3028::Time now;

  if (rtc.getTime(now)) {
    Serial.printf("Time: %02d:%02d:%02d\n", now.hour, now.min, now.sec);
  } else {
    Serial.println("Read error");
  }

  delay(1000);
}