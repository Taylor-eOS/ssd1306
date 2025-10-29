#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCL_PIN 4
#define SDA_PIN 3

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void drawDiagnostics() {
    display.drawRect(4, 20, 120, 40, WHITE);
    display.drawLine(4, 20, 124, 60, WHITE);
    display.drawLine(124, 20, 4, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(10, 50);
    display.print("Rotation 0 128x64");
    display.display();
}

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.display();
    delay(100);
    display.fillScreen(WHITE);
    display.display();
    delay(300);
    display.fillScreen(BLACK);
    display.display();
    delay(300);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(4, 4);
    display.print("SSD1315 Test");
    display.display();
    drawDiagnostics();
}

void loop() {
    display.invertDisplay(true);
    display.display();
    delay(400);
    display.invertDisplay(false);
    display.display();
    delay(400);
}
