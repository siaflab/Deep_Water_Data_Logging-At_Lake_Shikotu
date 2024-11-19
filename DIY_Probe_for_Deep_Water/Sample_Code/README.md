
<img width="400" src="https://github.com/siaflab/Deep_Water_Data_Logging_At_Lake_Shikotu/blob/main/DIY_Probe_for_Deep_Water/Sample_Code/DataLoggerShield.png" alt="DataLoggerShield" title="DataLoggerShield">  

New components added at locations 1 through 5 on the Data Logger Shield.

①This 4 pin connects to I2C of Pressure Sensor MS5837-30BA.

②The piezoelectric buzzer connected to pin 8 of Arduino Uno.

③This is a logic level conversion module for communicating between Arduino's 5V and 3.3V sensors via I2C.  
Pressure sensor MS5837-30BA and gyro sensor MPU-6050 are connected to the 3.3V side.

④This is a 6 axis gyro sensor MPU-6050 for recording the attitude of the payload.

⑤The 2 pin connector prepared to send the PWM signal from the 8-pin with a buzzer,
 and at the same time send a start signal to the external microphone terminal of the action camera. 
We use a 10μF capacitor and two 100K ohm as a simple voltage divider circuit next to the buzzer to match the level of the mini pin.

<img width="400" src="https://github.com/siaflab/Deep_Water_Data_Logging_At_Lake_Shikotu/blob/main/DIY_Probe_for_Deep_Water/Sample_Code/buzzer.png" alt="buzzer_sch" title="buzzer_sch">  

* [RTC_Setup.ino](https://github.com/siaflab/Deep_Water_Data_Logging_At_Lake_Shikotu/blob/main/DIY_Probe_for_Deep_Water/Sample_Code/RTC_Setup.ino)  
Use this program to record the current time on RTC before starting recording. 

* [DeepWaterLogger_sample.ino](https://github.com/siaflab/Deep_Water_Data_Logging_At_Lake_Shikotu/blob/main/DIY_Probe_for_Deep_Water/Sample_Code/DeepWaterLogger_sample.ino)
  This is a program that uses an Arduino data logger shield to record time stamps, water temperature, and water pressure on an SD card in CSV format.

* [DeepWaterLogger_with_MPU-6050](https://github.com/siaflab/Deep_Water_Data_Logging_At_Lake_Shikotu/blob/main/DIY_Probe_for_Deep_Water/Sample_Code/DeepWaterLogger_with_MPU-6050)  
It is used to check the momentum with a 6-axis gyro sensor.
