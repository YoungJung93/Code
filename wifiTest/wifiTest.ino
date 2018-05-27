#include <WiFi.h>

char ssid[] = "iPhone";     //  연결하실 와이파이 이름
char pass[] = "****";  // 네트워크 보안키
int status = WL_IDLE_STATUS;

void setup() {

  Serial.begin(9600); 
  while (!Serial) {
    ; // 시리얼 포트에 연결될 때까지 기다림(아두이노 레오나르도만 쓰면 됨)
  }
  
  // 현재 아두이노에 연결된 실드를 확인
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // 와이파이 실드가 아닐 경우
    while(true);
  } 
  
 // 와이파이에 연결 시도
  while ( status != WL_CONNECTED) { // 연결이 될 때 까지 반복
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // WPA/WAP2 네트워크에 연결
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
   
  // 연결에 성공했으면 연결확인 메시지와 연결된 네트워크 정보를 띄운다. 
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}

void loop() { 
  // 10초마다 네트워크 연결 확인을 해준다.
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // WI-FI 실드의 IP를 출력한다.
  IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);
  
  // MAC어드레스를 출력한다.
  byte mac[6];  
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
 
}

void printCurrentNet() {
  // 접속하려는 네트워크의 SSID를 출력한다.
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // 접속하려는 router의 MAC 주소를 출력한다.
  byte bssid[6];
  WiFi.BSSID(bssid);    
  Serial.print("BSSID: ");
  Serial.print(bssid[5],HEX);
  Serial.print(":");
  Serial.print(bssid[4],HEX);
  Serial.print(":");
  Serial.print(bssid[3],HEX);
  Serial.print(":");
  Serial.print(bssid[2],HEX);
  Serial.print(":");
  Serial.print(bssid[1],HEX);
  Serial.print(":");
  Serial.println(bssid[0],HEX);

  // 수신 신호 강도를 출력한다.
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // 암호화 타입을 출력한다.
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption,HEX);
  Serial.println();
}
