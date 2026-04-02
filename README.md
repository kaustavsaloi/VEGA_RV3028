# VEGA_RV3028

Custom Arduino library for RV-3028-C7 RTC optimized for VEGA boards.

## Features
- Multi-I2C support (TwoWire)
- EEPROM busy handling (EEbusy)
- Burst read for stable time
- Lightweight and fast

## Usage

```cpp
TwoWire myWire = TwoWire(1);
VEGA_RV3028 rtc(myWire);

rtc.begin();