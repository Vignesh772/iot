#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHTesp.h"
DHTesp dht;

const char* ssid = "Home 184_4G";
const char* password = "Vishnesh1607";

//Your Domain name with URL path or IP address with path
String serverName = "http://vignesh772.pythonanywhere.com/read";
unsigned long lastTime = 0;

unsigned long timerDelay = 10;
#define sensorPin A0
int rain_data = 0;
float temp_data = 0;
float hum_data = 0;

void setup() {
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

  dht.setup(14, DHTesp::DHT11); // GPIO14

}

int readSensor() {
  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog moisture value
}

void sendData()
{
   if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // String serverPath = serverName + "?temperature=24.37";
      String serverPath = serverName + "?rain=" + rain_data + "&temp=" + temp_data + "&hum=" + hum_data;
      Serial.println(serverPath);
      
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
void loop() {
  Serial.print("Analog output: ");
  rain_data = readSensor();
  hum_data = dht.getHumidity();
  temp_data = dht.getTemperature();
  Serial.print(rain_data);
  Serial.print(temp_data);
  Serial.print(hum_data);
  Serial.println();
  sendData();
  delay(500);


}
