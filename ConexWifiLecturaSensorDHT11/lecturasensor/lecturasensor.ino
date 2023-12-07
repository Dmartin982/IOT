#include <DHT.h>
#include <DHT_U.h>

DHT dht (D3,DHT11);

float temp, hume;
int pause=800;
unsigned long start_time;


void leerSensor (){
  hume = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.println ("Tempe=" + String(temp)+", Humed="+String(hume));
  };

void setup() {
 dht.begin();
 Serial.begin(115200);
 start_time=millis();
}

void loop() {
  if (millis()-start_time>=pause){
  leerSensor();
  start_time=millis();
  }
}
