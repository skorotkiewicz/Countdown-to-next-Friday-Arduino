# Arduino count to the next Friday

This is the first version of the countdown to the next Friday by the Arduino controller and RTC.
Feature, Arduino controller is put to sleep every second to reduce the energy demand.

You need:
 * Arduino
 * RTC
 * breadboard and wires

To set the date on RTC, just uncomment the lines before upload! :+1:

```c
RTC.adjust(DateTime(__DATE__, __TIME__));
```

### Photos

![Front](https://url.itunix.eu/5ZyIU)
![Back](https://url.itunix.eu/7ZYLE)
[GIF](https://gfycat.com/GrimBraveHairstreak)

### Libraries used to make this:

 * [LedControl](https://github.com/wayoda/LedControl/releases) for LED Display
 * [rtclib](https://github.com/adafruit/RTClib) for RTC Control