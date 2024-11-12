/*
 *This is a program that uses an Arduino data logger shield to record time stamps, 
 *water temperature, and water pressure on an SD card in CSV format.
 *A piezoelectric buzzer indicates an SD card error or the start of recording.
 *The water pressure sensor Blue Robotics MS5837-30BA can measure up to 30 bar (300m/1000ft deep) 
 *and communicates with the logger via I2C. 
 *Library:https://github.com/bluerobotics/BlueRobotics_MS5837_Library
 */
#include <SPI.h>
#include <SD.h>
const int chipSelect = 10;

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS1307 rtc;
String Filename;

// Blue Robotics MS5837
#include <Wire.h>
#include <MS5837.h>
MS5837 sensor;

//Speaker pin is digital pin 9
const int speakerPin = 9;

int cnt=0;

void setup () {
    pinMode(LED_BUILTIN, OUTPUT);

    tone(speakerPin,262,200);//C
    delay(200);
    tone(speakerPin,294,200);//D
    delay(200);
    tone(speakerPin,330,250);//E
    delay(1000);
    
  Serial.begin(57600);
  
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
  tone(speakerPin,262,400);//C
  delay(400);
  tone(speakerPin,330,400);//E
  delay(400);
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(__DATE__, __TIME__));

    DateTime time = rtc.now();
    //Full Timestamp
    //Filename = String(time.timestamp(DateTime::TIMESTAMP_FULL));
    Filename = String(time.timestamp(DateTime::TIMESTAMP_DATE));
    Filename.replace("-","");  Filename.replace(":",""); 
    Filename += ".txt";
    Serial.println(Filename);

    // Blue Robotics MS5837
    Wire.begin();
    // Initialize pressure sensor
    // Returns true if initialization was successful
    // We can't continue with the rest of the program unless we can initialize the sensor
    while (!sensor.init()) {
      Serial.println("Init failed!");
      Serial.println("Are SDA/SCL connected correctly?");
      Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
      Serial.println("\n\n\n");
      tone(speakerPin,262,400);   //C
      delay(400);
      tone(speakerPin,330,400);  //E
      delay(400);
    }
  
    // .init sets the sensor model for us but we can override it if required.
    // Uncomment the next line to force the sensor model to the MS5837_30BA.
    sensor.setModel(MS5837::MS5837_30BA);
  
    sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  while (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    tone(speakerPin,390,400);  //E
    delay(400);
    tone(speakerPin,330,400);   //G
    delay(400);
    // don't do anything more:
    //while (1);
  }
  Serial.println("card initialized.");

    File dataFile = SD.open(Filename, FILE_WRITE);   
    String Header = "Timestamp,Pressure(mbar),Temperature(deg C),Depth(m),Altitude( m above mean sea level)";
    dataFile.println(Header);
    dataFile.close();
    Serial.println(Header);

    tone(speakerPin,330,80);  //E
    delay(80);
    tone(speakerPin,0,40);  //E
    delay(40);
    tone(speakerPin,330,80);  //E
    delay(80);
}

void loop () {
  digitalWrite(LED_BUILTIN, HIGH); 

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  // File name up to 8 characters
  File dataFile = SD.open(Filename, FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    String dataString = "";
    
    DateTime time = rtc.now();

    //Full Timestamp
    dataString = String(time.timestamp(DateTime::TIMESTAMP_FULL))+",";

    sensor.read();

    dataString += String(sensor.pressure()) + ",";
    dataString += String(sensor.temperature()) + ",";
    dataString += String(sensor.depth()) + ",";
    dataString += String(sensor.altitude()) + ",";    
    dataString += String(cnt);    
    // print to the serial port too:
    Serial.println(dataString);

    dataFile.println(dataString);
    dataFile.close();
    cnt++;
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
    delay(100); 
    digitalWrite(LED_BUILTIN, LOW); 
    delay(850);
}
