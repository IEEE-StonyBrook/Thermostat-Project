/*
  Thermostat Project
  
  Outputs the results of a temperature-humidity sensor and a pressure-altitude
  sensor on a 4D Systems ÂµLCD-32PTU touchscreen, written for an Arduino Uno.
  
  Sensors communicate with Arduino using I2C; Arduino Uno as master, sensors 
  as slave mode.
  
 */

#include "MPL3115A2.h"
#include "HIH6130.h"
#include "Wire.h"

MPL3115A2 myPressure;
int main()
{
	setup();
	while(true)
	{
		loop();
	}
	return 0;
}
void setup()
{
  Wire.begin();        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  myPressure.begin(); // Get sensor online

  //Configure the sensor
  //myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
}

void loop()
{
  float pressure = myPressure.readPressure();
  Serial.print("Pressure(Pa):");
  Serial.print(pressure, 2);

  float temperature = myPressure.readTempF();
  float humidity;
  fetch_humidity_temperature(&humidity,&temperature);
  Serial.print(" Temp(f):");
  Serial.print(temperature, 2);
  delay 1000;

  //References: 
  //Definition of "altimeter setting": http://www.crh.noaa.gov/bou/awebphp/definitions_pressure.php
  //Altimeter setting: http://www.srh.noaa.gov/epz/?n=wxcalc_altimetersetting
  //Altimeter setting: http://www.srh.noaa.gov/images/epz/wxcalc/altimeterSetting.pdf
  //Verified against Boulder, CO readings: http://www.crh.noaa.gov/bou/include/webpres.php?product=webpres.txt
  
  //const int station_elevation_ft = 5374; //Must be obtained with a GPS unit
  //float station_elevation_m = station_elevation_ft * 0.3048; //I'm going to hard code this
  const int station_elevation_m = 1638; //Accurate for the roof on my house
  //1 pascal = 0.01 millibars
  pressure /= 100; //pressure is now in millibars

  float part1 = pressure - 0.3; //Part 1 of formula
  
  const float part2 = 8.42288 / 100000.0;
  float part3 = pow((pressure - 0.3), 0.190284);
  float part4 = (float)station_elevation_m / part3;
  float part5 = (1.0 + (part2 * part4));
  float part6 = pow(part5, (1.0/0.190284));
  float altimeter_setting_pressure_mb = part1 * part6; //Output is now in adjusted millibars
  float baroin = altimeter_setting_pressure_mb * 0.02953;

  Serial.print(" Altimeter setting InHg:");
  Serial.print(baroin, 2);

  Serial.println();
}


/* Friday, March 27, 2015
 * 
 * Today's task is to code working versions of these functions.
 * 
 */
 
 
double readThermometer() {
  //unsigned int temp;
  //fetch_humidity_temperature(temp);
  //return temp;
}

double readHygrometer(){

}

double readPressureSensor() {

}

