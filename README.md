# Curs Cornellà 2020

```
/curs Cornellà 2020
//Exercici 0
//06.03.2020
//nodeMCU
//@rPrimTech Jaume Nogués

//---------------------------------------------------------------------------------------------
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "aaaabbbbbcccccddddd"; 

char ssid[] = "WLAN_2020";
char pass[] = "12345678";
//---------------------------------------------------------------------------------------------

void setup()
{
Serial.begin(115200);
Serial.println(" ");
Serial.println("Comencem!");
Blynk.begin(auth, ssid, pass, IPAddress(167,86,87,117), 8080);
}

void loop()
{
Blynk.run();
}

```
