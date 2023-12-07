#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

DHT dht(D3, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiServer server(80);

String ssid = "Personal-956 2.4";
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

WiFiClient client = server.available(); //objeto de la clase WiFiClient
  // avalaible() detecta un cliente nuevo del objeto de la clase WifiServer
  if(!client){
    return;
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nuevo Cliente...");
  
  Serial.println("Nuevo cliente...");
  while(!client.available()){ //espera a un cliente diponible
    delay(1);
  }

  String peticion = client.readStringUntil('\r'); //lee la peticion del cliente
 // Serial.println(peticion);
  client.flush(); //limpia la peticion del cliente

  client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("");
  client.println("");
  client.println(""); 

    //INICIA LA PAGINA

  client.println("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<title>Estacion meteorologica</title></head>");
  client.println("<body style='font-family: Century gothic; width: 800;'><center>"); 
  client.println("<body style='font-family: Century gothic; width: 800;'><center>");
  client.println(" <div style='box-shadow: 0px 0px 20px 8px rgba(0,0,0,0.22); padding: 20px; width: 300px; display: inline-block; margin: 30px;'>"); 
  client.println("<h2>Temperatura = " + String(temp) + " C</h2>");
  client.println("<h2>Humedad = " + String(hume) + " %</h2>"); 
  client.println("</div></center></body></html>"); 
 
               
    //FIN DE LA PAGINA

  delay(10);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peticion finalizada");
  
  //Serial.println("Peticion finalizada");
  //Serial.println("");  
}





  
