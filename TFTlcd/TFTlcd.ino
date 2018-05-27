#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

#define cs   4
#define dc   6
#define rst  3

void back();
void front();
void right();
void left();

TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  Serial.begin(115200);
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  //back();
  front();
  //right();
  //left();
}

void loop() {
  
}

void back() {
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.line(80,124,40,64); TFTscreen.line(40,64,60,64);
  TFTscreen.line(60,64,60,4); TFTscreen.line(60,4,100,4);
  TFTscreen.line(100,4,100,64); TFTscreen.line(100,64,120,64);
  TFTscreen.line(120,64,80,124);
}
void front() {
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.line(60,124,60,64); TFTscreen.line(60,64,40,64);
  TFTscreen.line(40,64,80,4); TFTscreen.line(80,4,120,64);
  TFTscreen.line(120,64,100,64); TFTscreen.line(100,64,100,124);
  TFTscreen.line(100,124,60,124);
}
void right() {
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.line(20,84,80,84); TFTscreen.line(80,84,80,104);
  TFTscreen.line(80,104,140,64); TFTscreen.line(140,64,80,24);
  TFTscreen.line(80,24,80,44); TFTscreen.line(80,44,20,44);
  TFTscreen.line(20,44,20,84);
}
void left() {
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.line(20,64,80,104); TFTscreen.line(80,104,80,84);
  TFTscreen.line(80,84,140,84); TFTscreen.line(140,84,140,44);
  TFTscreen.line(140,44,80,44); TFTscreen.line(80,44,80,24);
  TFTscreen.line(80,24,20,64);
}

