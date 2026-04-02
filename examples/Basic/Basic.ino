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
    Serial.print("Time: ");

    if (now.hour < 10) Serial.print("0");
    Serial.print(now.hour);
    Serial.print(":");

    if (now.min < 10) Serial.print("0");
    Serial.print(now.min);
    Serial.print(":");

    if (now.sec < 10) Serial.print("0");
    Serial.println(now.sec);

    Serial.print("Date: ");
    Serial.print(now.date);
    Serial.print("/");
    Serial.print(now.month);
    Serial.print("/20");
    Serial.println(now.year);
  } else {
    Serial.println("RTC Read Failed!");
  }

  delay(1000);
}