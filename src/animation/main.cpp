#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCL_PIN 4
#define SDA_PIN 3
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int frame = 0;
int xPos = -20;

void drawStickFigure(int x, int y, int legAngle, int armAngle) {
    display.fillCircle(x + 8, y + 10, 6, WHITE);
    display.drawLine(x + 8, y + 16, x + 8, y + 36, WHITE);
    display.drawLine(x + 8, y + 22, x + 2 + armAngle, y + 30, WHITE);
    display.drawLine(x + 8, y + 22, x + 14 - armAngle, y + 30, WHITE);
    display.drawLine(x + 8, y + 36, x + 3 + legAngle, y + 50, WHITE);
    display.drawLine(x + 8, y + 36, x + 13 - legAngle, y + 50, WHITE);
}

void drawGround() {
    display.drawLine(0, 55, 127, 55, WHITE);
    display.drawLine(0, 56, 127, 56, WHITE);
}

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
}

void loop() {
    display.clearDisplay();
    drawGround();
    int legOffset = (frame % 8 < 4) ? 3 : -3;
    int armOffset = (frame % 8 < 4) ? -2 : 2;
    drawStickFigure(xPos, 8, legOffset, armOffset);
    display.drawPixel((xPos + 20 + frame) % 128, 57, WHITE);
    display.drawPixel((xPos + 50 + frame * 2) % 128, 58, WHITE);
    display.display();
    xPos += 1;
    if (xPos > 140) {
        xPos = -25;
    }
    frame++;
    if (frame > 10000) frame = 0;
    delay(60);
}
