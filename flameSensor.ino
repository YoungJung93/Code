#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include<stdlib.h>
#include "utility/debug.h"
#include "utility/socket.h"

#define ADAFRUIT_CC3000_IRQ   7
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
SPI_CLOCK_DIVIDER);

#define WLAN_SSID       "iPhone"
#define WLAN_PASS       "dud36wnd" 
#define WLAN_SECURITY   WLAN_SEC_WPA2
#define IDLE_TIMEOUT_MS  3000
#define WEBPAGE      "/exitGuidance/server.jsp"

char buffer[10];
const unsigned long
dhcpTimeout     = 60L * 1000L, // Max time to wait for address from DHCP
connectTimeout  = 15L * 1000L, // Max time to wait for server connection
responseTimeout = 15L * 1000L; // Max time to wait for data from server
uint32_t   t;
uint32_t ip = cc3000.IP2U32(172,20,10,2);
int port = 8080;

Adafruit_CC3000_Server server(8080);
Adafruit_CC3000_Client client;

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
  if (!cc3000.begin()) {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    return;
  }
  Serial.print(F("\nAttempting to connect to "));
  Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
  Serial.println(F("Connected!"));
  Serial.println(F("Request DHCP")); 
  
  while (!cc3000.checkDHCP()) // 자동 IP 할당
  {
    delay(100);
  }
  Serial.println(F("DHCP OK"));
  server.begin();
  Serial.println(F("Ready..."));
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
    sendData("1");
  }
  if (val_2 >= 3) {
    Serial.println("No.2 sensor fire!");
    sendData("2");
  }
  if (val_3 >= 3) {
    Serial.println("No.3 sensor fire!");
    sendData("3");
  }
  if (val_4 >= 3) {
    Serial.println("No.4 sensor fire!");
    sendData("4");
  }
  else {
    Serial.println("peace");
    sendData("0");
  }
  //readData();
  delay(5000);
  
} 
bool displayConnectionIp(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.println();
    return true;
  }
}
bool send_request (String request) {
  // Transform to char
  char requestBuf[request.length()+1];
  request.toCharArray(requestBuf,request.length()); 
  // Send request
  if (client.connected()) {
    client.fastrprintln(requestBuf); 
  } 
  else {
    Serial.println(F("Connection failed"));    
    return false;
  }
  return true;
  free(requestBuf);
}
void show_response() {
  Serial.println(F("-------------------------------------"));
  while (client.available()) {
    // Read answer and print to serial debug
    char c = client.read();
    Serial.print(c);
  }
}
char timedRead(void) {
  unsigned long start = millis();
  while((!client.available()) && ((millis() - start) < responseTimeout));
  return client.read();  // -1 on timeout
}
void sendData(String val) {
  t = millis();
  do {
    client = cc3000.connectTCP(ip, port);
  } 
  while((!client.connected()) &&
    ((millis() - t) < connectTimeout));
  if (client.connected()) {
    Serial.println("Connected"); 
    String request = "GET /exitGuidance/server.jsp?value=" + val + " HTTP/1.0\r\nConnection: close\r\n\r\n";
    Serial.print("...Sending request:");
    Serial.println(request);
    send_request(request);
//    String data="value="+val;
//    client.println("POST /exitGuidance/server.jsp HTTP/1.1"); 
//    client.println("Host: 124.28.43.165:8080"); // SERVER ADDRESS HERE TOO
//    client.println("Content-Type: application/x-www-form-urlencoded"); 
//    client.print("Content-Length: "); 
//    client.println(data.length()); 
//    client.println(); 
//    client.print(data);
  }
  else {
    Serial.println(F("Connection failed"));    
    return;
  }
  Serial.println("...Reading response");
  show_response();

  Serial.println(F("Cleaning up..."));
  Serial.println(F("...closing socket"));
  client.close();
//  if (client.connected()) { 
//    client.close();  // DISCONNECT FROM THE SERVER
//  }
}
//void readData() {
//  cc3000.printIPdotsRev(ip);
//  Serial.println();
//  client = cc3000.connectTCP(ip, port);
//  if (client.connected()) {
//    client.fastrprint(F("GET "));
//    client.fastrprint(WEBPAGE);
//    client.fastrprint(F(" HTTP/1.1\r\n"));
//    client.fastrprint(F("Host: ")); client.fastrprint("124.28.43.165"); client.fastrprint(F("\r\n"));
//    client.fastrprint(F("\r\n"));
//    client.println();
//  } else {
//    Serial.println(F("Connection failed"));    
//    return;
//  }
//
//  Serial.println(F("-------------------------------------"));
//  
//  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
//  unsigned long lastRead = millis();
//  while (client.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
//    while (client.available()) {
//      char c = client.read();
//      Serial.print(c);
//      lastRead = millis();
//    }
//  }
//  client.close();
//  Serial.println();
//  Serial.println(F("-------------------------------------"));
//  
//  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
//  /* the next time your try to connect ... */
//  Serial.println(F("\n\nDisconnecting"));
//  cc3000.disconnect();
//  
////  Adafruit_CC3000_ClientRef client = server.available();
////  if(client) { // 서버에서 데이터 읽어오기
////    if(client.connected()){
////      Serial.println("sucess") ;
////      uint8_t ch = client.read();
////      Serial.print(ch);
////      Serial.println();
////    }
////    else{
////      Serial.println("false");
////    }
////    delay(5000) ;
////  }
////  else Serial.println("fail");
//}

