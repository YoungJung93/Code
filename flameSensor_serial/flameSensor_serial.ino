#include <SoftwareSerial.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include<stdlib.h>
#include "utility/debug.h"
#include "utility/socket.h"

//#define ADAFRUIT_CC3000_IRQ   7
//#define ADAFRUIT_CC3000_VBAT  5
//#define ADAFRUIT_CC3000_CS    10
//Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
//SPI_CLOCK_DIVIDER);

//SoftwareSerial mySerial(8, 9);

int flame1 = A0; 
int flame2 = A1; 
int flame3 = A2; 
int flame4 = A3; 
int val_1 = 0, val_2 = 0, val_3 = 0, val_4 = 0; 

void setup() {
  pinMode(flame1, INPUT);
  pinMode(flame2, INPUT);
  pinMode(flame3, INPUT);
  pinMode(flame4, INPUT);
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop() {
  val_1 = analogRead(flame1); //Read the analog value
  val_2 = analogRead(flame2);
  val_3 = analogRead(flame3);
  val_4 = analogRead(flame4);
  Serial.print("No.1 : "); Serial.println(val_1);
  Serial.print("No.2 : "); Serial.println(val_2);
  Serial.print("No.3 : "); Serial.println(val_3);
  Serial.print("No.4 : "); Serial.println(val_4);

  if (val_1 >= 3) {
    Serial.println("No.1 sensor fire!");
    //mySerial.println(1);
  }
  else mySerial.println(5);
  if (val_2 >= 3) {
    Serial.println("No.2 sensor fire!");
    //mySerial.println(2);
  }
  else mySerial.println(6);
  if (val_3 >= 3) {
    Serial.println("No.3 sensor fire!");
    //mySerial.println(3);
  }
  else mySerial.println(7);
  if (val_4 >= 3) {
    Serial.println("No.4 sensor fire!");
    //mySerial.println(4);
  }
  else mySerial.println(8);
  else {
    Serial.println("peace");
    //mySerial.println(0);
  }
  delay(100);
}
