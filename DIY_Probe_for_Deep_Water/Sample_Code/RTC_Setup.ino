/*
*Use this program to record the current time on RTC before starting recording. 
*The Arduino data logger shield comes with a button battery, so you will know the current time until the battery runs out.
*Log data can be compared by referring to camera time.
*/
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  while (!Serial);
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("No RTC found");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is not configured");
  }
  // Set Date and Time (Year, DAY, Month, Hour(24h), Minute, Second)
  rtc.adjust(DateTime(2024, 11, 11, 1, 11, 11)); //Uncomment this line to set Date and Time
}

void loop () { // Get Date and Time
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('-');
  Serial.print(now.month(), DEC);
  Serial.print('-');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(3000);
}
