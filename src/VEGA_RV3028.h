#ifndef VEGA_RV3028_H
#define VEGA_RV3028_H

#include <Arduino.h>
#include <Wire.h>

#define RV3028_ADDR 0x52

class VEGA_RV3028 {
public:
    VEGA_RV3028(TwoWire &wire = Wire);

    bool begin();
    bool isConnected();

    struct Time {
        uint8_t sec;
        uint8_t min;
        uint8_t hour;
        uint8_t weekday;
        uint8_t date;
        uint8_t month;
        uint8_t year;
    };

    bool setTime(Time t);
    bool getTime(Time &t);

private:
    TwoWire *_wire;

    void waitReady();
    uint8_t bcdToDec(uint8_t val);
    uint8_t decToBcd(uint8_t val);
};

#endif