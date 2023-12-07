#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

DHT dht(D3, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiServer server(80);

String ssid = "Personal-956";
String password = "nMMhN9vW9S";
String Ip;
float temp, hume;
int pause = 800;
unsigned long start_time;
boolean estado=true;

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + String(ipAddress[1]) + String(".") + String(ipAddress[2]) + String(".") + String(ipAddress[3]);
}

void imprimir (){

if (estado==true) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(ssid);
  lcd.setCursor(0, 1);
  lcd.print(Ip);
  delay(5000);
  estado=false;
}
else {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tp= " + String(temp) + " C");
  lcd.setCursor(0, 1);
  lcd.print("H%= " + String(hume) + " %"); 
  }
}


void leerSensor()
{
  hume = dht.readHumidity();
  temp = dht.readTemperature();
  imprimir ();
  // Serial.println("T°=" + String(temp) + ", Humed=" + String(hume));
}

void setup()
{
  dht.begin();
  Serial.begin(115200);
  start_time = millis();
  lcd.init();
  lcd.backlight();

  // Conexión WIFI
  WiFi.begin(ssid, password);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando...");
  lcd.setCursor(0, 1);
  lcd.print("Intento: ");
  int i = 1;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    lcd.setCursor(10, 1);
    lcd.print(String(i));
    i++;
  }
 
Ip = IpAddress2String(WiFi.localIP());
imprimir();
server.begin();
}

void loop()
{
  if (millis() - start_time >= pause)
  {
    leerSensor();
    start_time = millis();
  }
}
