#include "SparkTime/SparkTime.h"

UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
unsigned long lastTime = 0UL;
String timeStr;
int hour;
int relay = D7;

void setup() {
  pinMode(relay, OUTPUT);
  rtc.begin(&UDPClient, "north-america.pool.ntp.org");
  rtc.setTimeZone(-8); // pst offset
  Serial.begin(9600);
  Particle.variable("pacificTime", timeStr);
  Particle.variable("hour", &hour, INT);
}

void loop() {
    currentTime = rtc.now();
    timeStr = rtc.hourString(currentTime);
    // hour = str.substr (3,5)
    hour = atoi(timeStr);
    // check time of day to control light
    if (hour>4 && hour<11) {
        digitalWrite(relay, HIGH);
    }
    if (hour>16 && hour<21) {
        digitalWrite(relay, HIGH);
    }
    else {
        digitalWrite(relay, LOW);
    }
}
