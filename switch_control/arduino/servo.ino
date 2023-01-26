// Include the Servo library 
#include <Servo.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Home 184_4G";
const char* password = "*******"

//Your Domain name with URL path or IP address with path
String serverName = "http://vignesh772.pythonanywhere.com/read";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
String prev_payload = "OFF";

unsigned long timerDelay = 10;

// Declare the Servo pin 
int servoPin = 2; 
// Create a servo object 
Servo Servo1; 

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

void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
   Servo1.write(75); 
     delay(1000);
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
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
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
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        if (payload=="ON")
        {
          if (prev_payload=="OFF")
          {
            prev_payload="ON";
            Serial.println("Changing state to  ON");
            Servo1.write(15); 
            delay(500);

            Servo1.write(75); 
            delay(1000);
            
          }
        }
        if (payload == "OFF")
        {
          if (prev_payload=="ON")
          {
            prev_payload="OFF";
          Serial.println("Changing state to OFF");
          Servo1.write(145); 
         delay(500);
      
         Servo1.write(75); 
         delay(1000);
          }
        }
        
        Serial.println(payload);
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