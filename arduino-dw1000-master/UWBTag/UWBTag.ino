/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsTag
 *  - give example description
 */
#include <WiFi.h>
#include <SPI.h>
#include "DW1000Ranging.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

const char *SSID = "ssid";
const char *PW = "pass";
const int PORT = 3000;
const char *URL = "localhost";
const char *HOST = "/";

int wifiStatus = 0;
boolean wifiAvailable = true;

WiFiClient wc;

void setup() {
  Serial.begin(9600);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY,false);

  if(WiFi.status() == WL_NO_SHIELD) { Serial.println("wifi error"); wifiAvailable = false; }
  else { Serial.println("wifi ok"); wifiAvailable = true; }

  while(wifiStatus != WL_CONNECTED) {
    Serial.println("connecting...");
    wifiStatus = WiFi.begin(SSID, PW);
    delay(1000);
  }
  Serial.println("wifi connected");
}

void loop() {
  DW1000Ranging.loop();
  Serial.println(DW1000Ranging.getXLocation(DW1000Ranging.getDistantDevice()->getShortAddress(),DW1000Ranging.getDistantDevice()->getRange()),2);
}

void newRange() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

//void sendDataToServer(float sendData) {
//  client.println("GET %s HTTP/1.1", HOST);
//  client.println(sendData);
//}

