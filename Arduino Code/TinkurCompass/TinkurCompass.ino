//////////////////////////////////////
//  Adam Zolyak
//  Val Zolyak
//  TinkurLab
//  www.TinkurLab.com
//  2015
//
//  This software is released under the GNU GENERAL PUBLIC LICENSE Version 3
//
//  This project makes use the of the following libraries and contributions by others:
//
/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 
 /***************************************************************************
  This is a library example for the HMC5883 magnentometer/compass

  Designed specifically to work with the Adafruit HMC5883 Breakout
  http://www.adafruit.com/products/1746
 
  *** You will also need to install the Adafruit_Sensor library! ***

  These displays use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries with some heading example from
  Love Electronics (loveelectronics.co.uk)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the version 3 GNU General Public License as
 published by the Free Software Foundation.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address
  
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop() {

  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Convert degrees to radians: http://www.rapidtables.com/convert/number/degrees-to-radians.htm
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.13; //Denver, CO, USA
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); 
  Serial.println(headingDegrees);
  
  Serial.print("Heading direction: "); 
  Serial.println(getHeadingDirection(headingDegrees));
  
  Serial.print("Heading direction friendly: "); 
  Serial.println(getHeadingDirectionFriendly(getHeadingDirection(headingDegrees)));
  
  matrix.setBrightness(16);
  
  // N
  matrix.clear();      // clear display  
  matrix.drawPixel(3, 0, LED_ON); 
  matrix.drawPixel(2, 1, LED_ON); 
  matrix.drawPixel(2, 2, LED_ON); 
  matrix.drawPixel(1, 2, LED_ON); 
  matrix.drawPixel(4, 1, LED_ON); 
  matrix.drawPixel(4, 2, LED_ON);
  matrix.drawPixel(5, 2, LED_ON); 
  matrix.drawPixel(3, 1, LED_ON); 
  matrix.drawPixel(3, 2, LED_ON); 
  matrix.drawPixel(3, 3, LED_ON); 
  matrix.drawPixel(3, 4, LED_ON); 
  matrix.drawPixel(3, 5, LED_ON);
  matrix.drawPixel(3, 6, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // NE
  matrix.clear();      // clear display 
  matrix.drawPixel(5, 0, LED_ON);  
  matrix.drawPixel(6, 0, LED_ON); 
  matrix.drawPixel(7, 0, LED_ON); 
  matrix.drawPixel(5, 2, LED_ON);
  matrix.drawPixel(4, 3, LED_ON);
  matrix.drawPixel(6, 1, LED_ON); 
  matrix.drawPixel(7, 1, LED_ON);
  matrix.drawPixel(7, 2, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // E
  matrix.clear();      // clear display 
  matrix.drawPixel(7, 3, LED_ON);  
  matrix.drawPixel(7, 4, LED_ON); 
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // SE
  matrix.clear();      // clear display 
  matrix.drawPixel(6, 7, LED_ON);  
  matrix.drawPixel(7, 6, LED_ON); 
  matrix.drawPixel(7, 7, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // S
  matrix.clear();      // clear display 
  matrix.drawPixel(3, 7, LED_ON);  
  matrix.drawPixel(4, 7, LED_ON); 
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // SW
  matrix.clear();      // clear display 
  matrix.drawPixel(0, 6, LED_ON);  
  matrix.drawPixel(0, 7, LED_ON); 
  matrix.drawPixel(1, 7, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // W
  matrix.clear();      // clear display 
  matrix.drawPixel(0, 3, LED_ON);  
  matrix.drawPixel(0, 4, LED_ON); 
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  // NW
  matrix.clear();      // clear display 
  matrix.drawPixel(0, 0, LED_ON);  
  matrix.drawPixel(0, 1, LED_ON); 
  matrix.drawPixel(1, 0, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

}

int getHeadingDirection(float degreesFromNorth) {
  
  int headingDirection;
  
  if (degreesFromNorth >= 337.5 || degreesFromNorth <= 22.5) {
    headingDirection = 1;
  } else if (degreesFromNorth > 22.5 && degreesFromNorth <= 67.5) {
    headingDirection = 2;
  } else if (degreesFromNorth > 67.5 && degreesFromNorth <= 112.5) {
    headingDirection = 3;
  } else if (degreesFromNorth > 112.5 && degreesFromNorth <= 157.5) {
    headingDirection = 4;
  } else if (degreesFromNorth > 157.5 && degreesFromNorth <= 202.5) {
    headingDirection = 5;
  } else if (degreesFromNorth > 202.5 && degreesFromNorth <= 247.5) {
    headingDirection = 6;
  } else if (degreesFromNorth > 247.5 && degreesFromNorth <= 292.5) {
    headingDirection = 7;
  } else if (degreesFromNorth > 292.5 && degreesFromNorth < 337.5) {
    headingDirection = 8;
  } else {
    headingDirection = 9;
  }
  
  return headingDirection;
}

String getHeadingDirectionFriendly(int headingDirection) {
  
  String headingDirectionFriendly;
  
  if (headingDirection == 1) {
    headingDirectionFriendly = "N";
  } else if (headingDirection == 2) {
    headingDirectionFriendly = "NE";
  } else if (headingDirection == 3) {
    headingDirectionFriendly = "E";
  } else if (headingDirection == 4) {
    headingDirectionFriendly = "SE";
  } else if (headingDirection == 5) {
    headingDirectionFriendly = "S";
  } else if (headingDirection == 6) {
    headingDirectionFriendly = "SW";
  } else if (headingDirection == 7) {
    headingDirectionFriendly = "W";
  } else if (headingDirection == 8) {
    headingDirectionFriendly = "NW";
  } else if (headingDirection == 9) {
    headingDirectionFriendly = "??";
  }
  
  return headingDirectionFriendly;
}
