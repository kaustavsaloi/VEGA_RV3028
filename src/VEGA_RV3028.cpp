#include "VEGA_RV3028.h"

VEGA_RV3028::VEGA_RV3028(TwoWire &wire) {
    _wire = &wire;
}

bool VEGA_RV3028::begin() {
    _wire->begin();
    waitReady();
    return isConnected();
}

bool VEGA_RV3028::isConnected() {
    _wire->beginTransmission(RV3028_ADDR);
    return (_wire->endTransmission() == 0);
}

void VEGA_RV3028::waitReady() {
    while (1) {
        _wire->beginTransmission(RV3028_ADDR);
        _wire->write(0x0E); // Status register
        _wire->endTransmission(false);

        _wire->requestFrom(RV3028_ADDR, 1);

        if (_wire->available()) {
            uint8_t status = _wire->read();
            if (!(status & 0x80)) { // EEbusy bit
                break;
            }
        }
        delay(5);
    }
}

bool VEGA_RV3028::setTime(Time t) {
    _wire->beginTransmission(RV3028_ADDR);
    _wire->write(0x00);

    _wire->write(decToBcd(t.sec));
    _wire->write(decToBcd(t.min));
    _wire->write(decToBcd(t.hour));
    _wire->write(t.weekday);
    _wire->write(decToBcd(t.date));
    _wire->write(decToBcd(t.month));
    _wire->write(decToBcd(t.year));

    return (_wire->endTransmission() == 0);
}

bool VEGA_RV3028::getTime(Time &t) {
    _wire->beginTransmission(RV3028_ADDR);
    _wire->write(0x00);

    if (_wire->endTransmission(false) != 0) return false;

    _wire->requestFrom(RV3028_ADDR, 7);

    if (_wire->available() < 7) return false;

    t.sec     = bcdToDec(_wire->read() & 0x7F);
    t.min     = bcdToDec(_wire->read() & 0x7F);
    t.hour    = bcdToDec(_wire->read() & 0x3F);
    t.weekday = _wire->read() & 0x07;
    t.date    = bcdToDec(_wire->read() & 0x3F);
    t.month   = bcdToDec(_wire->read() & 0x1F);
    t.year    = bcdToDec(_wire->read());

    return true;
}

uint8_t VEGA_RV3028::bcdToDec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

uint8_t VEGA_RV3028::decToBcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}