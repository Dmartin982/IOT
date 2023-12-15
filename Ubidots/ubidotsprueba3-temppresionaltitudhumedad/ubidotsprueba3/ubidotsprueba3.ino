#include <DHT.h>
#include <Ubidots.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include "libreriawifimanager.h"

#define pinLed2 D7
#define DEVICE_LABEL "weather-station"                                        //nombre del dispositivo en Ubidots
#define UBIDOTS_TOKEN  "BBUS-IzrBLnazbJ5H9WQSnotEYpbd7SpI5U"                  //token dispositivo
#define LAB_LED "Led"                                                         //nombre de las variables del dispositivo en Ubidots textuales
#define LAB_HUM "humidity"
#define LAB_TEMP "temperature"
#define LAB_PRES "atmospheric-pressure"
#define BMP280_ADDRESS (0x77)


float temp, pres;
int hum, led;


Ubidots ubidots (UBIDOTS_TOKEN, UBI_HTTP);
DHT dht (D3, DHT11);
Adafruit_BMP280 barometro;

void setup() {
pinMode(pinLed, OUTPUT);
pinMode(pinLed2, OUTPUT);
wifiConnection();

if (!barometro.begin()) {
Serial.println(F("Error: No se detecta sensor BMP280"));
while (1);
  }
 
dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  pres = barometro.readPressure()*10;
  ubidots.add(LAB_HUM, hum);
  ubidots.add(LAB_TEMP, temp);
  ubidots.add(LAB_PRES, pres);

  bool bufferSent = false;
  bufferSent = ubidots.send(DEVICE_LABEL);

  if (bufferSent) { Serial.println ("Values Sent"); };
  delay (1000);

}
