#include "LPD8806.h"
#include "SPI.h"
uint32_t Color;

int dataPin = 2;
int clockPin = 3;

int totalpixels = 32;
LPD8806 strip = LPD8806(totalpixels, dataPin, clockPin);

int anArray[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
int elements = sizeof(anArray) / sizeof(int);
//int randomArray;

void setup()
{
  Serial.begin(9600);
  int noise = analogRead(2);
  randomSeed(noise);
  strip.begin();
  strip.show();
  //shuffle(anArray, elements, sizeof(int));
  Serial.println("Test Program");
  
  
  
//for (i = 0; i < 31; i = i + 1) {
 // Serial.println(anArray[i]);
//}

}


void loop()
{


   randomFill();
   delay(1000);
   randomEmpty();
   delay(250);

  
}




// generate a value between 0 <= x < n, thus there are n possible outputs
int rand_range(int n)
{
    int r, ul;
    ul = RAND_MAX - RAND_MAX % n;
    while ((r = random(RAND_MAX+1)) >= ul);
    //r = random(ul);
    return r % n;
}


void shuffle_swap(int index_a, int index_b, int *array, int size)
{
    char *x, *y, tmp[size];

    if (index_a == index_b) return;

    x = (char*)array + index_a * size;
    y = (char*)array + index_b * size;

    memcpy(tmp, x, size);
    memcpy(x, y, size);
    memcpy(y, tmp, size);
}


// shuffle an array using fisher-yates method, O(n)
void shuffle(int *array, int nmemb, int size)
{
    int r;
    
    while (nmemb > 1) {                                                                      
        r = rand_range(nmemb--);                                                              
        shuffle_swap(nmemb, r, array, size);
    }
}

void randomFill(){
    int noise = analogRead(2);
    randomSeed(noise);
    shuffle(anArray, elements, sizeof(int));
    int i;
    int dwelltime;
    Color = randomColor();

    for (i = 0; i < 32; i = i + 1) {
      int pixel = anArray[i];
      strip.setPixelColor(pixel, Color);
      strip.show();
      dwelltime = random(0,250);
      delay(dwelltime);
      Serial.println(pixel);
    }
}
void randomEmpty(){
  int noise = analogRead(2);
  randomSeed(noise);
  shuffle(anArray, elements, sizeof(int));
  int i;
  int dwelltime;
  
    for (i = 0; i < 32; i = i + 1) {
    int pixel = anArray[i];
    byte r = 0;
    byte g = 0;
    byte b = 0;
    Color = strip.Color(r,g,b);
    strip.setPixelColor(pixel, Color);
    strip.show();
    dwelltime = random(5,100);
    delay(dwelltime);
    Serial.println(pixel);
    }    
}
uint32_t randomColor(){
  byte r = random(0,127);
  byte g = random(0,127);
  byte b = random(0,127);
  Color = strip.Color(r,g,b);
  return Color;
}


