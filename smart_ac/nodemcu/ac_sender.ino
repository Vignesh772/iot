
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
//#include <IRremote.hpp>

const char* ssid = "*****"
const char* password = "*****"

String serverName = "<your_api_endpoint>";

unsigned long lastTime = 0;
String prev_payload = "off";

unsigned long timerDelay = 10;


int khz = 38;
int irPin = D1; // pin IR led
IRsend irsend(irPin);
void setup()
{
  Serial.begin(9600);
  
  pinMode(irPin, OUTPUT);
   
  irsend.begin();
 //IrSender.begin(irPin);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  
}
void loop()
{
  const uint16_t offf[] ={980,570, 980,620, 930,2620, 930,2620, 930,620, 980,570, 980,2570, 980,2620, 930,620, 930,620, 980,2570, 980,570, 980,2570, 980,570, 980,620, 930,620, 930,620, 980,570, 980,570, 980,570, 980,620, 930,2620, 930,2620, 980,2570, 980,570, 980,570, 1030,570, 980,2570, 980,2570, 980,570, 980,570, 980,570, 1030,2520, 1030,570, 980,2570, 980,2570, 980,2570, 980,570, 1030,2520, 1030,570, 980,570, 980,570, 980,2570, 980,2570, 980,2570, 980,620, 930,2620, 930,620, 980,570, 980,570, 980,570, 980,570, 980,620, 930,620, 930,2620, 930,620, 980,2570, 980,570, 980,2620, 930,2620, 930,620, 930,2620, 980,570, 980,2570, 980,620, 930,620, 930,620, 930,620, 930,620, 980,570, 980,620, 930,620, 930,2620, 930,2620, 930,620, 980,2570, 980,2620, 930,620, 930,2620, 930,620, 930};  // Protocol=UNKNOWN Hash=0x492A8EEA 81 bits (incl. gap and start) received

  const uint16_t onn[] = {930,620, 980,570, 980,2620, 930,2620, 930,620, 980,570, 980,2570, 980,2570, 980,2620, 930,2620, 980,2570, 980,570, 980,2570, 980,570, 980,620, 930,620, 980,2570, 980,570, 980,570, 980,570, 980,620, 930,2620, 980,2620, 930,2570, 980,570, 980,570, 980,620, 930,2620, 930,2620, 930,620, 930,620, 930,670, 930,2620, 930,620, 930,620, 930,620, 930,2620, 930,2670, 930,2620, 930,620, 930,620, 930,620, 930,620, 930,620, 980,2620, 930,2620, 930,2620, 980,570, 980,570, 930,670, 930,2620, 930,620, 930,2620, 930,2620, 930,2620, 930,670, 880,2670, 930,620, 930,620, 930,2670, 880,670, 880,670, 880,2670, 930,2620, 930,620, 930,670, 880,670, 880,670, 880,670, 880,670, 930,670, 880,670, 880,2670, 880,2670, 880,2720, 830,720, 880,2670, 880,670, 880,670, 880,670, 880};  // Protocol=UNKNOWN Hash=0xEB807244 81 bits (incl. gap and start) received

  const uint16_t twentyfour[] = {930,620, 980,570, 980,2620, 930,2620, 930,620, 980,570, 980,2570, 980,2570, 980,2620, 930,2620, 980,2570, 980,570, 980,2570, 980,570, 980,620, 930,620, 980,2570, 980,570, 980,570, 980,570, 980,620, 930,2620, 980,2620, 930,2570, 980,570, 980,570, 980,620, 930,2620, 930,2620, 930,620, 930,620, 930,670, 930,2620, 930,620, 930,620, 930,620, 930,2620, 930,2670, 930,2620, 930,620, 930,620, 930,620, 930,620, 930,620, 980,2620, 930,2620, 930,2620, 980,570, 980,570, 930,670, 930,2620, 930,620, 930,2620, 930,2620, 930,2620, 930,670, 880,2670, 930,620, 930,620, 930,2670, 880,670, 880,670, 880,2670, 930,2620, 930,620, 930,670, 880,670, 880,670, 880,670, 880,670, 930,670, 880,670, 880,2670, 880,2670, 880,2720, 830,720, 880,2670, 880,670, 880,670, 880,670, 880};  // Protocol=UNKNOWN Hash=0xEB807244 81 bits (incl. gap and start) received

  const uint16_t eighteen[] = {930,620, 930,620, 930,2670, 930,2620, 930,620, 930,620, 930,2670, 880,2670, 880,2620, 980,2620, 930,2620, 930,620, 930,2670, 880,620, 930,620, 930,670, 930,2620, 880,670, 930,620, 930,620, 930,620, 930,2670, 880,2670, 880,2670, 930,620, 930,620, 930,620, 930,2670, 880,670, 880,670, 930,2620, 930,620, 930,2670, 880,670, 930,620, 930,620, 930,620, 930,2620, 930,670, 930,2620, 930,620, 930,620, 930,620, 930,620, 930,670, 930,2620, 930,620, 930,2620, 930,620, 930,620, 930,2670, 930,2620, 930,620, 930,2670, 880,2670, 880,2670, 880,2670, 930,620, 930,620, 930,2670, 880,670, 880,670, 880,2670, 880,2670, 930,670, 880,670, 880,670, 880,670, 880,720, 830,720, 880,670, 880,670, 880,2670, 880,2720, 830,2720, 830,2720, 880,670, 880,2670, 880,2670, 880,2720, 780};  // Protocol=UNKNOWN Hash=0xCA96883F 81 bits (incl. gap and start) received

  const uint16_t thirty[] = {980,570, 980,570, 980,2570, 980,2620, 930,570, 980,620, 980,2570, 980,2620, 930,2570, 980,2620, 930,2620, 930,620, 980,2570, 980,570, 980,570, 980,570, 980,2620, 930,620, 980,570, 980,570, 980,570, 980,2620, 930,2620, 980,2570, 980,570, 980,570, 980,570, 980,2620, 930,2620, 980,2570, 980,2570, 980,570, 980,2570, 980,620, 980,2570, 980,2570, 980,570, 980,570, 980,620, 930,2620, 980,570, 980,570, 980,2570, 980,2570, 980,620, 930,620, 930,620, 980,2570, 980,570, 980,620, 930,620, 930,620, 930,2620, 930,620, 930,2620, 930,2670, 930,2620, 930,620, 930,670, 880,670, 880,670, 880,670, 930,2620, 930,620, 930,670, 880,670, 880,670, 880,670, 930,620, 930,670, 880,670, 880,670, 880,2720, 830,2720, 880,670, 880,2670, 880,670, 880,720, 830,720, 830,720, 830};  // Protocol=UNKNOWN Hash=0x536531DC 81 bits (incl. gap and start) received


    // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;
      
      http.begin(client, serverPath.c_str());
  
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        
        String payload = http.getString();

        if(payload=="on" && prev_payload != "on" )
        {
          prev_payload = "on";
          Serial.println(payload);
          irsend.sendRaw(onn, sizeof(onn) / sizeof(uint16_t), khz);
          delay(5000);
          
        }
        else if(payload=="off" && prev_payload != "off" )
        {
          Serial.println(payload);
          prev_payload = "off";
          irsend.sendRaw(offf, sizeof(offf) / sizeof(uint16_t), khz);
          delay(5000);
           
        }
        else if(payload=="18" && prev_payload != "18" )
        {
          Serial.println(payload);
          prev_payload = "18";
          irsend.sendRaw(eighteen, sizeof(eighteen) / sizeof(uint16_t), khz);
          delay(5000);
          
        }
        else if(payload=="24" && prev_payload != "24" )
        {
          Serial.println(payload);
          prev_payload = "24";
          irsend.sendRaw(twentyfour, sizeof(twentyfour) / sizeof(uint16_t), khz);
          delay(5000);
          
        }
        else if(payload=="30" && prev_payload != "30" )
        {
          Serial.println(payload);
          prev_payload = "30";
          irsend.sendRaw(thirty, sizeof(thirty) / sizeof(uint16_t), khz);
          delay(5000);

        }
        else if(payload=="reset")
        {
          Serial.println(payload);
          prev_payload = "";
          

        }
      }
    
        
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
 
  
 
}
  
/*
irsend.sendRaw(offf, sizeof(offf) / sizeof(uint16_t), khz);

delay(5000);

irsend.sendRaw(thirty, sizeof(thirty) / sizeof(uint16_t), khz);

delay(5000);
*/
