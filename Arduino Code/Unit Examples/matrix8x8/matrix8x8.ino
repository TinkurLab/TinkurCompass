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

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address
}

void loop() {

  matrix.setBrightness(16);
  
  // N arrow
  matrix.clear();      // clear display 
  matrix.drawLine(3, 0, 3, 6, LED_ON);
  matrix.fillTriangle(1, 2, 3, 0, 5, 2, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // NE arrow
  matrix.clear();      // clear display 
  matrix.drawLine(2, 5, 7, 0, LED_ON);
  matrix.fillTriangle(4, 0, 7, 0, 7, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // E arrow
  matrix.clear();      // clear display 
  matrix.drawLine(1, 3, 7, 3, LED_ON);
  matrix.fillTriangle(5, 1, 5, 5, 7, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // SE arrow
  matrix.clear();      // clear display 
  matrix.drawLine(2, 2, 7, 7, LED_ON);
  matrix.fillTriangle(7, 4, 7, 7, 4, 7, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // S arrow
  matrix.clear();      // clear display 
  matrix.drawLine(4, 1, 4, 7, LED_ON);
  matrix.fillTriangle(2, 5, 4, 7, 6, 5, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // SW arrow
  matrix.clear();      // clear display 
  matrix.drawLine(5, 2, 0, 7, LED_ON);
  matrix.fillTriangle(0, 7, 0, 4, 3, 7, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // W arrow
  matrix.clear();      // clear display 
  matrix.drawLine(0, 4, 6, 4, LED_ON);
  matrix.fillTriangle(0, 4, 2, 2, 2, 6, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);
  
  // NW arrow
  matrix.clear();      // clear display 
  matrix.drawLine(0, 0, 5, 5, LED_ON);
  matrix.fillTriangle(0, 0, 0, 3, 3, 0, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);

}
