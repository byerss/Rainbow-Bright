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



#if defined(USB_SERIAL) || defined(USB_SERIAL_ADAFRUIT)
// this is for teensyduino support
int dataPin = 2;
int clockPin = 3;
#else


// the Leonardo pinouts
int dataPin = 2;
int clockPin = 3;
#endif

// Set the totalpixels variable to the NUMBER of pixels. 32 = 32 pixels in a row
// The LED strips are 32 LEDs per meter but you can extend/cut the strip

int totalpixels = 32;
LPD8806 strip = LPD8806(totalpixels, dataPin, clockPin);



void setup() {
  
   Serial.begin(9600);
   randomSeed(analogRead(0)); 
 
   

  // Start up the LED strip
  strip.begin();
  
  // Update the strip, to start they are all 'off'
  strip.show();
  
  //Give Instructions on Console
  Serial.println("* Adafruit Addressable RGB LED Strip Individual Pixel Test Program *");
  Serial.println("");
  Serial.println("Instructions: Change an individual pixel by entering values in the format i,r,g,b");
  Serial.println("where i is the pixel number index and r/g/b are 7-bit brightness values (0 to 127).");
  //Serial.println("Line Ending must be set to Newline.");
  Serial.println("");
}



void loop() {
  // If there's any serial available, read it:
 
  
  while (Serial.available() > 0) {

    //Read the CSV from the serial port and parse to separate varibles:
    int pixel = Serial.parseInt();
    int red = Serial.parseInt(); 
    int green = Serial.parseInt(); 
    int blue = Serial.parseInt(); 

    //Continue after newline is detected
    if (Serial.read() == '\n' ) {
      
      //Check to make sure pixel is within range
      if (pixel > totalpixels - 1 || pixel < 0){
        Serial.println("Invalid Pixel!");
        Serial.println("");
      }
        else
      {
      //Contrain the input data to valid values      
      byte r = abs(0 - constrain(red, 0, 127));
      byte g = abs(0 - constrain(green, 0, 127));
      byte b = abs(0 - constrain(blue, 0, 127));
      
      //convert to i and c for strip.setPixelColor(i,c);
      int i = pixel;
      
      Color = strip.Color(r,g,b);
      
      //Write the color to the pixel
      strip.setPixelColor(i, Color);
      
      //Update the Strip
      strip.show();
      
      
      Serial.print("Pixel Number ");
      Serial.print(i);
      Serial.print(" set to ");      
      

      Serial.print(r);
      Serial.print(",");
      Serial.print(g);
      Serial.print(",");
      Serial.print(b);
      Serial.print(" (");
      Serial.print(Color, HEX);
      Serial.print(")");      
      Serial.println("");
      }
    }
  }
 } 
    
  

