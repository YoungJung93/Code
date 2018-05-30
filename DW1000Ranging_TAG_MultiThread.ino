

/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsTag
 *  - give example description
 */
#include <SPI.h>
#include <TFT.h>
#include "DW1000Ranging.h"
#include <j2thread.h>

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

float d1,d2,d3=0;
int i,j,k=0;
int l,r,f,b=0;

#define cs   4
#define dc   6
#define rst  3

void back();
void front();
void right();
void left();
void era_back();
void era_front();
void era_right();
void era_left();

TFT TFTscreen = TFT(cs, dc, rst);


void setup() {
  Serial.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  DW1000Ranging.useRangeFilter(true);
  
  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY,false);
  add_thread(new J2ThreadUnit(&loop1));
  add_thread(new J2ThreadUnit(&loop2));

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  //back();
  //front();
  //right();
  //left();
}

bool loop1(J2ThreadUnit* th)
{
  DW1000Ranging.loop();
  if(DW1000Ranging.getDistantDevice()->getShortAddress()==00){
    d1=DW1000Ranging.getDistantDevice()->getRange()+0.6;
    i=1;
  }
   else if(DW1000Ranging.getDistantDevice()->getShortAddress()==01){
    d2=DW1000Ranging.getDistantDevice()->getRange()-0.5;
    j=1;
  }
   else if(DW1000Ranging.getDistantDevice()->getShortAddress()==02){
    d1=DW1000Ranging.getDistantDevice()->getRange()+1.0;
    k=1;
  }
  if(i&&j&&k){
  Serial.print("X: ");Serial.println(DW1000Ranging.getXLocation(d1,d2,d3,0.9,0,0.9,0.6),2);
  Serial.print("Y: ");Serial.println(DW1000Ranging.getYLocation(d1,d2,d3,0.9,0,0.9,0.6),2);
    
}
bool loop2(J2ThreadUnit* th)
{
  if(DW1000Ranging.getXLocation(d1,d2,d3,0.9,0,0.9,0.6)>0){
      if(r==1){
        era_right();
        r=0;
      }

      else if(l==1){
        era_left();
        l=0;
      }

      else if(b==1){
        era_back();
        b=0;
      }
      
      else if(f==1){
        era_front();
        f=0;
      }
      else if(f==0){
        front();
        f=1;
      }
    }
    if(DW1000Ranging.getXLocation(d1,d2,d3,0.9,0,0.9,0.6)<0){

      if(r==1){
        era_right();
        r=0;
      }

      else if(l==1){
        era_left();
        l=0;
      }
      
      else if(f==1){
        era_front();
        f=0;
      }
      else if(r==1){
        era_right();
        r=0;
      }
      else if(f==0&&r==0){
        right();
        r=1;
      }
    }
    i=0;j=0;k=0;
  }
}
}
void newRange() {

}

void newDevice(DW1000Device* device) {
  //Serial.print("ranging init; 1 device added ! -> ");
 // Serial.print(" short:");
  //Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  //Serial.print("delete inactive device: ");
  //Serial.println(device->getShortAddress(), HEX);
}


void back() {
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.line(80,124,40,64); TFTscreen.line(40,64,60,64);
  TFTscreen.line(60,64,60,4); TFTscreen.line(60,4,100,4);
  TFTscreen.line(100,4,100,64); TFTscreen.line(100,64,120,64);
  TFTscreen.line(120,64,80,124);
}

void era_back() {
  TFTscreen.stroke(0, 0, 0);
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

void era_front() {
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.line(60,124,60,64); TFTscreen.line(60,64,40,64);
  TFTscreen.line(40,64,80,4); TFTscreen.line(80,4,120,64);
  TFTscreen.line(120,64,100,64); TFTscreen.line(100,64,100,124);
  TFTscreen.line(100,124,60,124);
}

void right() {
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.line(20,84,80,84); TFTscreen.line(80,84,80,104);
  TFTscreen.line(80,104,140,64); TFTscreen.line(140,64,80,24);
  TFTscreen.line(80,24,80,44); TFTscreen.line(80,44,20,44);
  TFTscreen.line(20,44,20,84);
}

void era_right() {
  TFTscreen.stroke(0,0,0);
  TFTscreen.line(20,84,80,84); TFTscreen.line(80,84,80,104);
  TFTscreen.line(80,104,140,64); TFTscreen.line(140,64,80,24);
  TFTscreen.line(80,24,80,44); TFTscreen.line(80,44,20,44);
  TFTscreen.line(20,44,20,84);
}

void left() {
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.line(20,64,80,104); TFTscreen.line(80,104,80,84);
  TFTscreen.line(80,84,140,84); TFTscreen.line(140,84,140,44);
  TFTscreen.line(140,44,80,44); TFTscreen.line(80,44,80,24);
  TFTscreen.line(80,24,20,64);
}

void era_left() {
  TFTscreen.stroke(0,0,0);
  TFTscreen.line(20,64,80,104); TFTscreen.line(80,104,80,84);
  TFTscreen.line(80,84,140,84); TFTscreen.line(140,84,140,44);
  TFTscreen.line(140,44,80,44); TFTscreen.line(80,44,80,24);
  TFTscreen.line(80,24,20,64);
}

