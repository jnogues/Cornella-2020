
//curs Cornellà 2020
//Exercici 3
//06.03.2020
//nodeMCU
//@rPrimTech Jaume Nogués
//---------------------------------------------------------------------------------------------
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "aaaaaabbbbbbbcccccccddddd"; 

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

char ssid[] = "IoT2";
char pass[] = "pitufito";
BlynkTimer timer;
//---------------------------------------------------------------------------------------------

int temperaturaLimit=27;
int comptadorNotificacionsTemperatura0=0;
int comptadorNotificacionsTemperatura1=0;
boolean alarmaT0=0;
boolean alarmaT1=0;
boolean clearT0=0;
boolean clearT1=0;

void setup()
{
// Debug console
pinMode(16, OUTPUT);
Serial.begin(115200);
Serial.println(" ");
Blynk.begin(auth, ssid, pass, IPAddress(xx,xx,xx,xx), 8080);
timer.setInterval(1000L, intermita);
timer.setInterval(10000L, uptime);
timer.setInterval(20000L, enviaTemperaturaDS18B20);
timer.setInterval(120000L, resetComptadorNotificacions);
timer.setInterval(21000L, textAlarma);
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
  if (t >= temperaturaLimit && comptadorNotificacionsTemperatura0<3)
    {
    Blynk.notify("OJO, ALARMA Temperatura 0!!");
    Serial.printf("[%u] OJO, ALARMA Temperatura 0!!", millis());
    Serial.println("");
    comptadorNotificacionsTemperatura0++;
    alarmaT0=1; 
    }
  if (t1 >= temperaturaLimit && comptadorNotificacionsTemperatura1<3)
    {
    Blynk.notify("OJO, ALARMA Temperatura 1!!");
    Serial.printf("[%u] OJO, ALARMA Temperatura 1!!", millis());
    Serial.println("");
    comptadorNotificacionsTemperatura1++;
    alarmaT1=1; 
    }  
}

void resetComptadorNotificacions()
{
  comptadorNotificacionsTemperatura0=0;
  comptadorNotificacionsTemperatura1=1;
  Serial.printf("[%u] RESET Alarmes", millis());
  Serial.println("");
}

void textAlarma()
{
  if (alarmaT0==1 && clearT0==0)
  {
  Blynk.virtualWrite(V21,"ALARMA O ACTIVA!");
  Blynk.setProperty(V21, "color", "#D3435C");//VERMELL
  clearT0=1;
  }
  if (alarmaT1==1 && clearT1==0)
  {
  Blynk.virtualWrite(V22,"ALARMA 1 ACTIVA!");
  Blynk.setProperty(V22, "color", "#D3435C");//VERMELL
  clearT1=1;
  }
}

BLYNK_WRITE(V30)
{
  Blynk.setProperty(V21, "color", "#23C48E");//VERD
  Blynk.setProperty(V22, "color", "#23C48E");
  Blynk.virtualWrite(V21,"OK");
  Blynk.virtualWrite(V22,"OK");
  clearT0=0;
  clearT1=0;
  alarmaT0=0;
  alarmaT1=0;
}

BLYNK_CONNECTED() 
{
  Blynk.syncAll();
  Blynk.setProperty(V21, "color", "#23C48E");//VERD
  Blynk.setProperty(V22, "color", "#23C48E");
  Blynk.virtualWrite(V21,"OK");
  Blynk.virtualWrite(V22,"OK"); 
}
