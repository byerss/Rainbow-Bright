#include "LPD8806.h"
#include "SPI.h"
uint32_t Color;

long randPixel;
long offsetR;
long offsetG;
long offsetB;
long randR;
long randG;
long randB;

int dataPin = 2;
int clockPin = 3;

int totalpixels = 32;
LPD8806 strip = LPD8806(totalpixels, dataPin, clockPin);

void setup() {

   Serial.begin(9600);
   randomSeed(analogRead(0)); 
   strip.begin();
   strip.show();
}

void loop() {

      offsetR = random(0,127);
      offsetG = random(0,127);
      offsetB = random(0,127);
      randPixel = random(0,32);
      randR = random(0,127) - offsetR;
      randG = random(0,127) - offsetG;
      randB = random(0,127) - offsetB;
      
      
      int i = randPixel;
      byte r = abs(0 - constrain(randR, 0, 127));
      byte g = abs(0 - constrain(randG, 0, 127));
      byte b = abs(0 - constrain(randB, 0, 127));
      
      Color = strip.Color(r,g,b);
      
      //Write the color to the pixel
      strip.setPixelColor(i, Color);
      
      //Update the Strip
      strip.show();
      delay(100);
      
      
  
    Serial.print("Pixel Number ");
    Serial.print(randPixel);
    Serial.print(" set to ");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.println(b);
    Serial.println(""); 
  
  
  
}
