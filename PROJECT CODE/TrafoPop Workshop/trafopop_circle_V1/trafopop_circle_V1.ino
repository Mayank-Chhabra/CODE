/*
This code was written in the 2nd TrafoPop workshop:
 http://www.trafopop.com/build-your-own-led-jacket-131102/
 
 This code was modified from Stefan Hintz's TrafoPop code:
 https://github.com/Stefan-Hintz/trafopop (Branch: "sh")
 The code treats the first two LEDs as individually addressable 
 and the last 18 LEDs are organzed in a circle and treated as a
 line.
 
 This code reads the position of your finger on a softpot and 
 uses the incoming values to control which LEDs are on and which are off.
 Softpot tutorial:
 http://bildr.org/2012/11/touch-sliders-with-a-softpot-arduino/
 
 Photos of the jacket:
 http://www.flickr.com/photos/plusea/sets/72157637300354054/
 
 Video of the jacket:
 http://www.youtube.com/watch?v=T6wYrtwq3fk
 */

// include SPI library for communication protocol with LED modules:
#include <SPI.h>

// define the number of your LEDs here:
#define NUM 20

// Variables:
long framecount = 0;
int fadeCount = 0;
int fadeAmount = 1;
int sensorValue;
float red;
float green;
float blue;
int count;
boolean setPosition = false;

// define data type struct color:
typedef struct color { 
  byte r, g, b; 
} 
color;

// color array for pixels. each pixel contains: r,g,b values between [0-255]
color pixels[NUM];

struct color colorOFF = { 
  0,0,0 };
struct color colorON = { 
  254, 254, 254 };


void setup() {
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV16);  // 1 MHz
  //SPI.setClockDivider(SPI_CLOCK_DIV8);  // 2 MHz
  // SPI.setClockDivider(SPI_CLOCK_DIV4);  // 4 MHz 

  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(A1, INPUT_PULLUP);
  digitalWrite(14, LOW);
  digitalWrite(16, HIGH);
  Serial.begin(9600);
}


void show(byte *bytes, int size) {
  for (int index=0; index<size; index++)
  {
    // nur 25% Helligkeit    
    byte c = bytes[index] >> 2;

    for (SPDR = c; !(SPSR & _BV(SPIF)););
  }
}


void loop() {
  sensorValue = analogRead(A1);  // read sensor value
  sensorValue = map(sensorValue, 0, 1000, 0, NUM-2);  // map sensor value to number of LEDs
  Serial.println(sensorValue);  // print sensor value to serial port for debugging

  // only if sensor is touched should it update LEDs on/off, otherwise keep last state:
  if(sensorValue != 18) {
    drawCircle();  // call drawCircle function
    show((byte *)pixels, sizeof(pixels));  // update pixels
    delay(2);
  }
}









