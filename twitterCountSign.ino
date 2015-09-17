#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

char buffer[10];
int displayNum;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.fillScreen(0);
  drawT();
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7,0,0));  
}

void loop() {
  listenForTweets();
  wipeNumbers();
  centerCursor();
  matrix.print(displayNum);
}

void listenForTweets() {
  if (Serial.available() > 0) {
    int index = 0;
    delay(100);
    int digits = Serial.available();
    while (digits--) {
      buffer[index++] = Serial.read();
    }
    displayNum = convertToInt(buffer);
  }
}

int convertToInt(char* data) {
  Serial.print("Data entered: ");
  Serial.println(data);
  return atoi(data);
}

void drawT() {
  matrix.fillRect(13,0,2,7,matrix.Color333(0,0,7));
  matrix.fillRect(15,2,3,2,matrix.Color333(0,0,7));
  matrix.drawPixel(18,3,matrix.Color333(0,0,7));
  matrix.fillRect(14,6,4,2,matrix.Color333(0,0,7));
  matrix.drawPixel(18,7,matrix.Color333(0,0,7));
}

void centerCursor() {
  if (displayNum < 10) {
    matrix.setCursor(13, 9);
  } else if (displayNum >= 10 && displayNum < 100) {
    matrix.setCursor(10, 9);
  } else if (displayNum >= 100 && displayNum < 1000) {
    matrix.setCursor(7, 9);
  } else if (displayNum >= 1000 && displayNum <10000) {
    matrix.setCursor(4, 9);
  } else {
    matrix.setCursor(1, 9);
  }
}

void wipeNumbers() {
  matrix.fillRect(0, 9, 32, 7, matrix.Color333(0,0,0));
}

