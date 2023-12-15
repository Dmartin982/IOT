#include <DHT.h>
#include <Ubidots.h>
#include "libreriawifimanager.h"

#define pinLed2 D7
#define DEVICE_LABEL "weather-station"                                        //nombre del dispositivo en Ubidots
#define UBIDOTS_TOKEN  "BBUS-IzrBLnazbJ5H9WQSnotEYpbd7SpI5U"                  //token dispositivo
#define LAB_LED "Led"                                                         //nombre de las variables del dispositivo en Ubidots textuales
#define LAB_HUM "humidity"
#define LAB_TEMP "temperature"


float temp;
int hum, led;


Ubidots ubidots (UBIDOTS_TOKEN, UBI_HTTP);
DHT dht (D3, DHT11);


void setup() {
pinMode(pinLed, OUTPUT);
pinMode(pinLed2, OUTPUT);
wifiConnection();
dht.begin();
temp = 0; 
hum = 0; 
led = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  ubidots.add(LAB_HUM, hum);
  ubidots.add(LAB_TEMP, temp);

  bool bufferSent = false;
  bufferSent = ubidots.send(DEVICE_LABEL);

  if (bufferSent) { Serial.println ("Values Sent"); };
  delay (1000);

}
