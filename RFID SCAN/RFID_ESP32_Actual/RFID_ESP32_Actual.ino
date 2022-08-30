 #include <SPI.h>
#include <RFID.h>
#include <esp_now.h>
#define SS_PIN 21
#define RST_PIN 22
#include "WiFi.h"

RFID rfid(SS_PIN, RST_PIN);

//const char* ssid     = "Realme3";
//const char* password = "12345678";

int LED = 2;
int buzzer = 4;
// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;
int count = 0;
String data;
String device_id = "0001"; //---------------------------------EDIT HERE-----------
int count_num_1 = 0;
int count_num_2 = 0;
int count_num_3 = 0;
int count_num_4 = 0;
int count_num_5 = 0;
int count_num_6 = 0;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("OK");
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    count_num_1 = 0;
    count_num_2 = 0;
    count_num_3 = 0;
    count_num_4 = 0;
    count_num_5 = 0;
    count_num_6 = 0;
    ESP.restart();    
  } else {
    Serial.println("Fail");
    if(count_num_1 < 25){
      Serial.println("Fail Master 01");
      count_num_1 = count_num_1 + 1;
      esp_err_t result = esp_now_send(new uint8_t[6] { 0x30, 0x83, 0x98, 0x00, 0x69, 0x24 }, (uint8_t*)data.c_str(), data.length());
      if (result != ESP_OK) {
        Serial.println("Send error");
      }
    }else if(count_num_1 == 25 && count_num_2 < 25){
      Serial.println("Fail Master 02");
      count_num_2 = count_num_2 + 1;
      esp_err_t result = esp_now_send(new uint8_t[6] { 0x58, 0xBF, 0x25, 0x36, 0x0F, 0xF0 }, (uint8_t*)data.c_str(), data.length());
      if (result != ESP_OK) {
        Serial.println("Send error");
      }
    }else if(count_num_1 == 25 && count_num_2 == 25 && count_num_3 < 25){
      Serial.println("Fail Master 03");
      count_num_3 = count_num_3 + 1;
      esp_err_t result = esp_now_send(new uint8_t[6] { 0x9C, 0x9C, 0x1F, 0xCB, 0x47, 0x3C }, (uint8_t*)data.c_str(), data.length());
      if (result != ESP_OK) {
        Serial.println("Send error");
      }
    }else if(count_num_1 == 25 && count_num_2 == 25 && count_num_3 == 25 && count_num_4 < 25){
      Serial.println("Fail Master 04");
      count_num_4 = count_num_4 + 1;
      esp_err_t result = esp_now_send(new uint8_t[6] { 0x84, 0xCC, 0xA8, 0x2C, 0xA2, 0x14 }, (uint8_t*)data.c_str(), data.length());
      if (result != ESP_OK) {
        Serial.println("Send error");
      } 
    }else if(count_num_1 == 25 && count_num_2 == 25 && count_num_3 == 25 && count_num_4 == 25 && count_num_5 < 25){
      Serial.println("Fail Master 05");
      count_num_5 = count_num_5 + 1;
      esp_err_t result = esp_now_send(new uint8_t[6] { 0x84, 0xCC, 0xA8, 0x2C, 0x76, 0x50 }, (uint8_t*)data.c_str(), data.length());
      if (result != ESP_OK) {
        Serial.println("Send error");
      } 
    }else if(count_num_1 == 25 && count_num_2 == 25 && count_num_3 == 25 && count_num_4 == 25 && count_num_5 == 25 && count_num_6 < 25){
      Serial.println("Fail Master 06");
      count_num_6 = count_num_6 + 1;
      esp_err_t result = esp_now_send(new uint8_t[6] { 0x58, 0xBF, 0x25, 0x35, 0xE5, 0xD8 }, (uint8_t*)data.c_str(), data.length());
      if (result != ESP_OK) {
        Serial.println("Send error");
      } 
    }else if(count_num_1 == 25 && count_num_2 == 25 && count_num_3 == 25 && count_num_4 == 25 && count_num_5 == 25 && count_num_6 == 25){
      digitalWrite(LED,HIGH);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(LED,LOW);
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(LED,HIGH);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(LED,LOW);
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(LED,HIGH);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(LED,LOW);
      digitalWrite(buzzer,HIGH);
      delay(300);
      ESP.restart();    
    }
}
}

void setup()
{
  int count_setup_reset = 0;
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(LED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);
  WiFi.mode(WIFI_STA);
//  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);
  esp_now_init();
  esp_now_register_send_cb(OnDataSent);

  static esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, new uint8_t[6] { 0x9C, 0x9C, 0x1F, 0xCB, 0x47, 0x3C }, 6); // 1
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
  static esp_now_peer_info_t peerInfo2;
  memcpy(peerInfo2.peer_addr, new uint8_t[6] { 0x84, 0xCC, 0xA8, 0x2C, 0xA2, 0x14 }, 6); // 2
  peerInfo2.channel = 0;
  peerInfo2.encrypt = false;
  if (esp_now_add_peer(&peerInfo2) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
  static esp_now_peer_info_t peerInfo3;
  memcpy(peerInfo3.peer_addr, new uint8_t[6] { 0x84, 0xCC, 0xA8, 0x2C, 0x76, 0x50 }, 6); // 3 
  peerInfo3.channel = 0;
  peerInfo3.encrypt = false;
  if (esp_now_add_peer(&peerInfo3) != ESP_OK) {
    Serial.println("Failed to add peer");
  }

  static esp_now_peer_info_t peerInfo4;
  memcpy(peerInfo4.peer_addr, new uint8_t[6] { 0x58, 0xBF, 0x25, 0x36, 0x0F, 0xF0 }, 6); // 1
  peerInfo4.channel = 0; 
  peerInfo4.encrypt = false;
  if (esp_now_add_peer(&peerInfo4) != ESP_OK) {
    Serial.println("Failed to add peer");
  }

  static esp_now_peer_info_t peerInfo5;
  memcpy(peerInfo5.peer_addr, new uint8_t[6] { 0x30, 0x83, 0x98, 0x00, 0x69, 0x24 }, 6); // 2
  peerInfo5.channel = 0;
  peerInfo5.encrypt = false;
  if (esp_now_add_peer(&peerInfo5) != ESP_OK) {
    Serial.println("Failed to add peer");
  }

  static esp_now_peer_info_t peerInfo6;
  memcpy(peerInfo6.peer_addr, new uint8_t[6] { 0x58, 0xBF, 0x25, 0x35, 0xE5, 0xD8 }, 6); // 3
  peerInfo6.channel = 0;
  peerInfo6.encrypt = false;
  if (esp_now_add_peer(&peerInfo6) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
  
//  while (WiFi.status() != WL_CONNECTED) 
//  {
//      delay(250);
//      Serial.print(".");
//      digitalWrite(LED,HIGH);
//      delay(250);
//      digitalWrite(LED,LOW);
//      delay(250);
//      count_setup_reset = count_setup_reset + 1;
//      if(count_setup_reset == 7){
//        ESP.restart();
//      }
//  }

  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");                            
  Serial.println(WiFi.macAddress());
  Serial.println("Device NO. : " + device_id); //-- -------------------------------------------------------------------------EDIT
  SPI.begin();
  rfid.init();
}

void loop()
{
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
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
        
        //buzzer
        digitalWrite(LED,HIGH);
        digitalWrite(buzzer,LOW);
        delay(500);
        digitalWrite(LED,LOW);
        digitalWrite(buzzer,HIGH);
        delay(300); //-------------------------------------------------------------------------------------------------------------------

        
        /// for Communication ------------------------------------------------------------------
        data = String("GET http://172.21.3.2/Input/connectR01.php?&dec="+ DEC_ALL +"&hex="+ HEX_ALL +"&device_id="+ device_id +"!");
        //String data = "HTTP://__________________________________";
        Serial.print("Sending... ");
        esp_err_t result = esp_now_send(new uint8_t[6] { 0x30, 0x83, 0x98, 0x00, 0x69, 0x24 }, (uint8_t*)data.c_str(), data.length());
        if (result != ESP_OK) {
          Serial.println("Send error");
        }
        delay(2000);
        /// END for Communication -------------------------------------------------------------------
        
      } 
    }
  

  rfid.halt();

  
}
