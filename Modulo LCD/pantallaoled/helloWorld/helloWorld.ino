#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Usa la librería LiquidCrystal_I2C

// Dirección I2C del módulo LCD, ajusta esto a tu dirección
int lcdAddress = 0x27;

// Inicializa el objeto LCD I2C
LiquidCrystal_I2C lcd(lcdAddress, 16, 2);  // 16 columnas, 2 filas

void setup() {
  // Inicializa el LCD
  lcd.init();
  lcd.backlight();  // Enciende la retroiluminación

  // Muestra "Hello, World!" en el LCD
  lcd.setCursor(0, 0); // Establece la posición del cursor en la primera fila, primera columna
  lcd.print("Hello, World!");

  delay(2000); // Espera 2 segundos
}

void loop() {
  // Tu código loop aquí
}
