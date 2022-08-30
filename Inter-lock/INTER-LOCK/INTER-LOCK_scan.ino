 #include <SPI.h>
#include <RFID.h>
#include <esp_now.h>
#define SS_PIN 21
#define RST_PIN 22
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <Wire.h>
#include <esp_wifi.h>

RFID rfid(SS_PIN, RST_PIN);
//String line = "a";
//const char* ssid     = "Realme3";
//const char* password = "12345678";
//char server[] = "192.168.82.204";
//String ip = "192.168.82.204:5000";
//String ip_only = "192.168.82.204";
//int port = 5000;                       //---------------------------------- default = 80

String line = "b";
const char* ssid     = "TYM IoT-N";
const char* password = "Geek@IT&asb2020";
char server[] = "172.21.3.2";
String ip = "172.21.3.2";
String ip_only = "172.21.3.2";
int port = 80; 

uint8_t newMACAddress[] = {0x94, 0xB9, 0x7E, 0xFB, 0x08, 0xBC}; //----------edit here !!!

WiFiClient client;

int R_RFID = 25;
int G_RFID = 26;
int B_RFID = 27;

int but = 5;
int Status = 4;
int LED = 2;
int Red = 13;
int Green = 12;
int Blue = 14;
int buzzer = 15;
// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;
int count = 0;
String data;
int mem_but = 0;

void GREEN_led (){
  digitalWrite(Red,LOW);
  digitalWrite(Green,HIGH);
  digitalWrite(Blue,LOW);
}
void BLUE_led (){
  digitalWrite(Red,LOW);
  digitalWrite(Green,LOW);
  digitalWrite(Blue,HIGH);
}
void RED_led (){
  digitalWrite(Red,HIGH);
  digitalWrite(Green,LOW);
  digitalWrite(Blue,LOW);
}
void NO_led (){
  digitalWrite(Red,LOW);
  digitalWrite(Green,LOW);
  digitalWrite(Blue,LOW);
}
void RED_RFID(){
  digitalWrite(R_RFID,HIGH);
  digitalWrite(G_RFID,LOW);
  digitalWrite(B_RFID,LOW);
}
void GREEN_RFID(){
  digitalWrite(R_RFID,LOW);
  digitalWrite(G_RFID,HIGH);
  digitalWrite(B_RFID,LOW);
}
void BLUE_RFID(){
  digitalWrite(R_RFID,LOW);
  digitalWrite(G_RFID,LOW);
  digitalWrite(B_RFID,HIGH);
}
void NO_RFID(){
  digitalWrite(R_RFID,LOW);
  digitalWrite(G_RFID,LOW);
  digitalWrite(B_RFID,LOW);
}

void setup()
{
  int count_setup_reset = 0;
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(Red,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(Blue,OUTPUT);
  pinMode(R_RFID,OUTPUT);
  pinMode(G_RFID,OUTPUT);
  pinMode(B_RFID,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(Status,OUTPUT);
  digitalWrite(Status,HIGH);
  pinMode(but,INPUT);
//  digitalWrite(buzzer,HIGH);
//  delay(500);
//  digitalWrite(buzzer,LOW);
  WiFi.mode(WIFI_STA);
  Serial.print("[OLD] ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  
  // ESP32 Board add-on before version < 1.0.5
  //esp_wifi_set_mac(ESP_IF_WIFI_STA, &newMACAddress[0]);
  
  // ESP32 Board add-on after version > 1.0.5
  esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);                          // uncomment here for need to change MAC address
  
  Serial.print("[NEW] ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
      digitalWrite(Status,HIGH);
      delay(250);
      Serial.print(".");
      digitalWrite(LED,HIGH);
      BLUE_led();
      delay(250);
      digitalWrite(LED,LOW);
      NO_led();
      delay(250);
      count_setup_reset = count_setup_reset + 1;
      if(count_setup_reset == 7){
        ESP.restart();
      }
  }

  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");                            
  Serial.println(WiFi.macAddress());
  
  SPI.begin();
  rfid.init();
}

void get_all_status(){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient client;
    client.begin("http://"+ ip +"/get_status/all_status_b.php");
    int httpCode = client.GET();

    if (httpCode > 0) {
      String payload = client.getString();
      DynamicJsonDocument doc(1024); 
      deserializeJson(doc, payload);
      String status_now = doc["status"];
      Serial.print("Status : ");
      Serial.println(status_now);
      client.end();
      if(status_now == "false"){
        digitalWrite(Status,LOW);
        RED_led();
        Serial.println("LOCK");
      }else if(status_now == "true") {
        digitalWrite(Status,HIGH);
        GREEN_led();
        Serial.println("UNLOCK");
      }
    }
    else{
      Serial.println("Error on HTTP Request");
      digitalWrite(Status,HIGH);
      BLUE_led();
      Serial.println("UNLOCK");
    }

    // client.end();
  }
}

void RFID_scan(){
  if (rfid.isCard()) {
    Serial.println("start scan 1");
    if (rfid.readCardSerial()) {
        Serial.println("start scan 2");
        /* With a new cardnumber, show it. */
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];
        
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        String DEC0 = String(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        String DEC1 = String(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        String DEC2 = String(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        String DEC3 = String(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        String DEC4 = String(rfid.serNum[4], DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        String HEX0 = String(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        String HEX1 = String(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        String HEX2 = String(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        String HEX3 = String(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        String HEX4 = String(rfid.serNum[4], HEX);
        Serial.println(" ");
       
        String DEC_ALL = String( DEC0 + DEC1 + DEC2 + DEC3 + DEC4);
        String HEX_ALL = String( HEX0 + HEX1 + HEX2 + HEX3 + HEX4);
        Serial.println(DEC_ALL);
        Serial.println(HEX_ALL);
        NO_RFID();
        //buzzer
        digitalWrite(LED,HIGH);
        digitalWrite(buzzer,HIGH);
        BLUE_RFID();
        delay(500);
        digitalWrite(LED,LOW);
        digitalWrite(buzzer,LOW);
        NO_RFID();
        delay(300); //-------------------------------------------------------------------------------------------------------------------

        record(DEC_ALL);
        /// for Communication ------------------------------------------------------------------
        
        delay(2000);
        mem_but = 0;
        /// END for Communication -------------------------------------------------------------------
        
      } 
      
    }
  

  rfid.halt();
}

void input() {
  if (client.connect(server, port)) {
      Serial.println("GET http://"+ ip +"/get_status/inter_lock_input.php?line=" + line);
      client.print("GET http://"+ ip +"/get_status/inter_lock_input.php?line=" + line);
      client.print(" ");
      client.print("HTTP/1.1");
      client.println();
      client.println("Host: "+ ip);
      client.println("Connection: close");
      client.println();
      delay(500);
      Serial.println("Start Record");
 }
 else {
    // if you didn't get a connection to the server:
    Serial.println("Connection Failed");
  }
}

void record(String dec) {
  if (client.connect(server, port)) {
      Serial.println("GET http://"+ ip +"/get_status/inter_lock_record.php?line=" + line + "&dec=" + dec);
      client.print("GET http://"+ ip +"/get_status/inter_lock_record.php?line=" + line + "&dec=" + dec);
      client.print(" ");
      client.print("HTTP/1.1");
      client.println();
      client.println("Host: "+ ip);
      client.println("Connection: close");
      client.println();
      delay(500);
      Serial.println("Start Record");
 }
 else {
    // if you didn't get a connection to the server:
    Serial.println("Connection Failed");
  }
}

void loop()
{
  int count_setup_reset = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
      digitalWrite(Status,HIGH);
      delay(250);
      Serial.print(".");
      digitalWrite(LED,HIGH);
      BLUE_led();
      delay(250);
      digitalWrite(LED,LOW);
      NO_led();
      delay(250);
      count_setup_reset = count_setup_reset + 1;
      if(count_setup_reset == 7){
        ESP.restart();
      }
  }
  get_all_status();
  delay(200);
  if(digitalRead(but) == LOW){
    NO_led();
    delay(200);
    input();
    mem_but = 1;
  }
  int count_down = 0;
  while(mem_but == 1){
    Serial.println("COUNT DOWN : " + String(count_down));
    BLUE_led();
    GREEN_RFID();
    RFID_scan();
    delay(500);
    if(count_down == 20 or digitalRead(but) == LOW){
      mem_but = 0;
      RED_RFID();
      delay(700);
      break;
    }
    NO_RFID();
    
    count_down++;
    delay(500);
  }
  

  
}
