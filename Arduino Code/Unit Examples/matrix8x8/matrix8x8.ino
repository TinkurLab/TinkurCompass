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
