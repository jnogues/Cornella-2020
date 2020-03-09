
//curs Cornellà 2020
//Exercici 2
//06.03.2020
//nodeMCU
//@rPrimTech Jaume Nogués
//---------------------------------------------------------------------------------------------
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "aaaabbbbbbccccccddddd"; 

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

char ssid[] = "IoT2";
char pass[] = "pitufito";
BlynkTimer timer;
//---------------------------------------------------------------------------------------------


void setup()
{
// Debug console
pinMode(16, OUTPUT);
Serial.begin(115200);
Serial.println(" ");
Blynk.begin(auth, ssid, pass, IPAddress(XX,XX,XX,XX), 8080);
timer.setInterval(1000L, intermita);
timer.setInterval(10000L, uptime);
timer.setInterval(20000L, enviaTemperaturaDS18B20);
DS18B20.begin();
}

void loop()
{
Blynk.run();
timer.run();
}


//---------------------------------------------------------------------------------------------
void intermita()
{
digitalWrite(16, !digitalRead(16));
}

void uptime()
{
Blynk.virtualWrite(V20, millis() / 1000);
}

void enviaTemperaturaDS18B20()
{
  DS18B20.requestTemperatures(); 
  float t = DS18B20.getTempCByIndex(0);
  Blynk.virtualWrite(V0,t);
  Serial.printf("[%u] temperatura 0 = %.2f", millis(), t);
  Serial.println("");
  float t1 = DS18B20.getTempCByIndex(1);
  Blynk.virtualWrite(V1,t1);
  Serial.printf("[%u] temperatura 1 = %.2f", millis(), t1);
  Serial.println("");
}
