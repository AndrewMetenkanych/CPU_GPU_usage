#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

char ssid[] = "Kavuneva_sich";          //  your network SSID (name)
char pass[] = "330room330";   // your network password

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiServer server(55555);  // Вказуємо порт для сервера

int CPU_Load = 0;
int RAM_Load = 0;
int GPU_Load = 0;
int GPU_Temperature = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.begin();  // Запускаємо сервер

  Wire.begin(4, 5);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Can`t find the device!"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Waiting for data..."));
  display.display();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");
    String jsonData = "";

    while (client.connected()) {
      while (client.available()) {
        char c = client.read();
        jsonData += c;
      }
    }

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, jsonData);

    CPU_Load = doc["cpu_usage"];
    RAM_Load = doc["ram_usage"];
    GPU_Load = doc["gpu_load"];
    GPU_Temperature = doc["gpu_temp"];

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("CPU: "); display.print(CPU_Load); display.println("%");
    display.print("RAM: "); display.print(RAM_Load); display.println("%");
    display.print("GPU: "); display.print(GPU_Load); display.print("% ");
    display.print(GPU_Temperature); display.println("C");
    display.display();

    client.stop();
    Serial.println("Client disconnected");
  }
}
