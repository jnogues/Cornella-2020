//curs Cornellà 2020
//Exercici 0
//06.03.2020
//nodeMCU
//@rPrimTech Jaume Nogués

//---------------------------------------------------------------------------------------------
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "aaaabbbbbcccccddddd"; 

char ssid[] = "IoT2";
char pass[] = "pitufito";
//---------------------------------------------------------------------------------------------

void setup()
{
Serial.begin(115200);
Serial.println(" ");
Serial.println("Comencem!");
Blynk.begin(auth, ssid, pass, IPAddress(xx,xx,xx,xx), 8080);
}

void loop()
{
Blynk.run();
}
