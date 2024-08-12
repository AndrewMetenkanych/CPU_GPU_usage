#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

char ssid[] = "Kavuneva_sich";          //  your network SSID (name)
char pass[] = "tiaminnitrat";   // your network password


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1

//I2C-адреса дисплея (0x3C за замовчуванням)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WebServer server(80);

int CPU_Load =0;
int RAM_Load =0;
int GPU_Load = 0;
int GPU_Temperature =0;


void handleClient(){
  if (server.hasArg("plain") == false) { 
    server.send(400, "text/plain", "Body not received");
    return;
  }

  String body = server.arg("plain");
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, body);

  CPU_Load = doc["cpu_usage"];
  RAM_Load = doc["ram_usage"];
  GPU_Load = doc["gpu_load"];
  GPU_Temperature = doc["gpu_temp"];

  // Display update
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("CPU: "); display.print(CPU_Load); display.println("%");
  display.print("RAM: "); display.print(RAM_Load); display.println("%");
  display.print("GPU: "); display.print(GPU_Load); display.print("% ");
  display.print(GPU_Temperature); display.println("C");
  display.display();

  server.send(200, "text/plain", "Data updated");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

Serial.println("Connected to WiFi");

server.on("/update", HTTP_POST, handleClient);
  server.begin();

  // Піни для SDA та SCL
  Wire.begin(4, 5);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Cunt find the device!"));
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
  server.handleClient();
}


