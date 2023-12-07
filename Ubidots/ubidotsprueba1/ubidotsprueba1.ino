#include <Ubidots.h>

const char* UBIDOTS_TOKEN = "BBUS-IzrBLnazbJ5H9WQSnotEYpbd7SpI5U";
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

Ubidots ubidots (UBIDOTS_TOKEN, UBI_HTTP);
int variable;


void setup() {
Serial.begin (115200);
ubidots.wifiConnect (WIFI_SSDI,WIFI_PASS);
variable=0;

}

void loop() {
  // put your main code here, to run repeatedly:
  ubidots.add("variable", variable);
  bool. bufferSent = false;
  bufferSent = ubidots.send();

  if (bufferSent) { Serial.println ("Values Sent") }
  delay (1000);

}
