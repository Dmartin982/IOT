#include <ESP8266WiFi.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Ticker.h>
#define pinLed D6

String Ip;

WiFiManager wifiManager;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Ticker ticker;


/////////////////////////////////////////////////////////////Funciones/////////////////////////////////////////////////

void imprimirMensajeEnLCD(String mensaje, int columna, int fila) {
  lcd.setCursor(columna, fila);
  lcd.print(mensaje);
}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + String(ipAddress[1]) + String(".") + String(ipAddress[2]) + String(".") + String(ipAddress[3]);
}

void parpadeoLed(){
  // Cambiar de estado el LED
  byte estado = digitalRead(pinLed);
  digitalWrite(pinLed, !estado);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {

  pinMode(pinLed, OUTPUT);
  ticker.attach(0.2, parpadeoLed);
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  //wifiManager.resetSettings(); // olvida las credenciales de la ultima conexion wifi
  imprimirMensajeEnLCD ("Connecting....", 0, 0);
  
  // Intenta conectarse a una red Wi-Fi
    wifiManager.setTimeout(30);
    if (!wifiManager.autoConnect("MiNodeMcu")){
    lcd.clear();
    imprimirMensajeEnLCD ("Connection error", 0, 0);
    delay (3000);
    lcd.clear();
    imprimirMensajeEnLCD ("AP Mode ON", 0, 0);
    delay (3000);
    ESP.restart();
      }
    
 // Logra conectarse a un wifi 
    Ip = IpAddress2String(WiFi.localIP());
    lcd.clear();
    imprimirMensajeEnLCD ("Connected!", 0, 0);
    delay(3000);
    lcd.clear();
    imprimirMensajeEnLCD (Ip, 0, 0);
    delay (5000);
    lcd.clear ();
    ticker.detach();
    digitalWrite(pinLed, LOW); 
  }


void loop() {
  // Tu código principal aquí
  imprimirMensajeEnLCD ("Welcome to Wapp!", 0, 0);
  
}
