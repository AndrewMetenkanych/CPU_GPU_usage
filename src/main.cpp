#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>


/* На потім
char ssid[] = "Kavuneva_sich";          //  your network SSID (name)
char pass[] = "tiaminnitrat";   // your network password
*/
///////////////////////////////////////////////////////////////////////////////////////////////
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1

//I2C-адреса дисплея (0x3C за замовчуванням)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int CPU_Load =0;
int CPU_Temperature = 0;
int GPU_Load = 0;
int GPU_Temperature =0;
int RAM_Load =0;
int RAM_Temperature =0;

void setup() {
  // Піни для SDA та SCL
  Wire.begin(4, 5); // SDA на GPIO 4, SCL на GPIO 5

  // Ініціалізуємо дисплей
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Cunt find the device!"));
    for(;;);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Pile of shit!"));
  display.display();
}

void loop() {
  // Основний код
}

