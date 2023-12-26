/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL2EtyfM61o"
#define BLYNK_TEMPLATE_NAME "LED"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

const int LED1 = D1;
const int LED2 = D2;

#include "BlynkEdgent.h"

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  digitalWrite (LED1, HIGH);
  delay (1000);
  digitalWrite (LED1, LOW);
  
  digitalWrite (LED2, HIGH);
  delay (1000);
  digitalWrite (LED2, LOW);
  
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}


BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(LED1, pinValue);
}

BLYNK_WRITE(V1) {
  int pinValue1 = param.asInt();
  digitalWrite(LED2, pinValue1);
}
