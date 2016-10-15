#include <Wire.h>
#include <RTClib.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <LedControl.h>
#include "nextFriday.h"

RTC_DS1307 RTC;
LedControl lc=LedControl(13, 12, 11, 1); // LedControl(int dataPin, int clkPin, int csPin, int numDevices);

int bis;
long nextFriday;
long result;
int wakePin = 2;

void setup () {

    Wire.begin();
    RTC.begin();

    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));

    // Initialize the MAX7219 device 
    lc.shutdown(0,false); // Enable display 
    lc.setIntensity(0,5); // Set brightness level (0 is min, 15 is max) 
    lc.clearDisplay(0); // Clear display register

    // save to rtc sqw signal ever 1 Hz
    Wire.beginTransmission(0x68);  
    Wire.write(0x07);  // 0x0E move register pointer to control register
    Wire.write(B00010000);     // set to 1Hz  
    Wire.endTransmission();

    // get the time and initialize
    getTime();

    // sleep config
    pinMode(wakePin, INPUT);
    attachInterrupt(0, wakeUpNow, FALLING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
}


void loop () {

    if ( result != 0 ) {
        time(result);
        sleep_cpu();
    } else {
        getTime();
    }

}

void time(long val){  
    int days = elapsedDays(val);
    int hours = numberOfHours(val);
    int minutes = numberOfMinutes(val);
    int seconds = numberOfSeconds(val);

     printSeconds(seconds);
     printMinutes(minutes);
     printHours(hours);
     printDays(days); 

}

void printSeconds(int v) {
    int ones;
    int tens;

    ones=v%10;
    v=v/10;
    tens=v;

    lc.setDigit(0,1,(byte)tens,false);
    lc.setDigit(0,0,(byte)ones,false);
}

void printMinutes(int v) {
    int ones;
    int tens;

    ones=v%10;
    v=v/10;
    tens=v;

    lc.setDigit(0,3,(byte)tens,false);
    lc.setDigit(0,2,(byte)ones,true);
}

void printHours(int v) {
    int ones;
    int tens;

    ones=v%10;
    v=v/10;
    tens=v;

    lc.setDigit(0,5,(byte)tens,false);
    lc.setDigit(0,4,(byte)ones,true);
}

void printDays(int v) {
    int ones;
    int tens;

    ones=v%10;
    v=v/10;
    tens=v;

    //lc.setDigit(0,7,(byte)tens,false);
    lc.setDigit(0,6,(byte)ones,true);
}

void getTime() {

    DateTime now = RTC.now();

    int wd = now.dayOfWeek();

    if ( wd == 0) {
        bis = 2;
    } else if ( wd == 1) {
        bis = 3;
    } else if ( wd == 2) {
        bis = 4;
    } else if ( wd == 3) {
        bis = 5;
    } else if ( wd == 4) {
        bis = 6;
    } else if ( wd == 5) {
        bis = 0;
    } else if ( wd == 6) {
        bis = 1;
    } else {}

    nextFriday  = 604800-((bis * 86400)+(now.hour()*3600)+(now.minute()*60)+now.second());
    result = (nextFriday + 43200); //12*3600=43200

}

void wakeUpNow() {
    result--;
}