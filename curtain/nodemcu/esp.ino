#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Home 184_4G";
const char* password = "Vishnesh1607";

//Your Domain name with URL path or IP address with path
String serverName = "http://vignesh772.pythonanywhere.com/read";

unsigned long lastTime = 0;
String prev_payload = "0";

unsigned long timerDelay = 10;

String str;
void setup(){
Serial1.begin(9600);
Serial.begin(9600);
WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  get_initial_state();
}



void get_initial_state(){
   if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // String serverPath = serverName + "?temperature=24.37";
      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        prev_payload = payload;
      
    
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



void loop(){ 
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // String serverPath = serverName + "?temperature=24.37";
      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        //Serial.print("HTTP Response code: ");
        //Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        Serial.println(prev_payload);
        
        if (payload.toInt()>prev_payload.toInt())
        {
          int change = map(payload.toInt()-prev_payload.toInt(), 0, 100, 0, 2048*4);
          String command = String(change) + "F";
          Serial1.println(command);
          prev_payload=payload;
        }
        if (payload.toInt()<prev_payload.toInt())
        {
          int change = map(prev_payload.toInt()-payload.toInt(), 0, 100, 0, 2048*4);
          String command = String(change) + "T";
          Serial1.println(command);
          prev_payload=payload;
        }
     
        
        //Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
 
  
 
}
