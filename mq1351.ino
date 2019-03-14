#include "MQ135.h"
#include <ESP8266WiFi.h>
#define ANALOGPIN A0
WiFiClient client;
String apiKey = "Z1T563WF17IV62TW";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "Moto G3 TE";     // replace with your wifi ssid and wpa2 key
const char *pass =  "physics@science";
const char* server = "api.thingspeak.com";
MQ135 gasSensor = MQ135(ANALOGPIN);
//int sum =0;
//int den=1;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    WiFi.disconnect();
    delay(10);
    WiFi.begin(ssid, pass);
    Serial.println();
    Serial.println("Connecting to ");
    Serial.println(ssid);
     while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
   pinMode(5, OUTPUT);  // pinmode for led
}


void loop() {
  digitalWrite(5, LOW);
  // put your main code here, to run repeatedly:
  float ppm = gasSensor.getPPM();
  //float rzero = gasSensor.getRZero();
  
  Serial.println(ppm);
  /**Serial.println(rzero);
  sum=sum+rzero;
  float avg=(sum)/den;
  den=den+1;
  Serial.println("avg=");
 Serial.print(avg);**/

  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(ppm);
                             postStr += String("\r\n\r\n");
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  if(ppm>400)
  {
      digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)

  }

  else
  {
    digitalWrite(5, LOW); // turn the LED off (LOW  the voltage level)
  }

  
  
    delay(1600);
}
