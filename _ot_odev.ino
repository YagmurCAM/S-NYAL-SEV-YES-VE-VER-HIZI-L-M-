/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include <ESP32Ping.h>
#include <HTTPClient.h>
  

const char* ssid     = "Yagmur";
const char* password = "iotsifrem";
String avg_time_ms;
char buf[16];
const char* domain = "https://jsonplaceholder.typicode.com/todos";
float fileSize = 0.1899;
float katsayi =100.0;
int i;


void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    
    WiFi.mode(WIFI_STA); // mode static
    WiFi.disconnect(); // bağlantı kes
   
    delay(100); 

    Serial.println("Setup done");
    
}

void loop()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
      
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }

    
     WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");  // Just for troubleshot purpose.  
  Serial.println(WiFi.localIP());

 
    HTTPClient http;
 unsigned long start=millis();

  
    http.begin(domain); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        unsigned long  finished=millis();
  unsigned long elapsed=finished-start;
  float buff = (float)elapsed/(float)1000;
 

 float temp = fileSize/buff;
 Serial.print("hız :");
  Serial.print(katsayi * temp);

 Serial.print("Mbps");
  

      }
 
    else {
      Serial.println("Error on HTTP request");
    }
    http.end(); //Free the resources
  
  Serial.println("\n");
      WiFi.disconnect();

  delay(5000);


 }
