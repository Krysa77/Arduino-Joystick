#include <Arduino.h>
 
// Definice pinů
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int swPin = 6;
const int vrxPin = A0;
const int vryPin = A1;
 
int colorState = 0; // 0 = zelená, 1 = červená, 2 = modrá
int intensity = 0; // Intenzita LED (0-255)
 
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP); // Aktivace interního pull-up rezistoru
}
 
void loop() {
  // Změna barvy při stisknutí tlačítka
  static unsigned long lastDebounceTime = 0;
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(swPin);
 
  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastDebounceTime) > 300) {
    colorState = (colorState + 1) % 3; // Přejdi na další barvu
    lastDebounceTime = millis(); // Nastav čas pro debouncing
  }
 
  lastButtonState = buttonState;
 
  // Čtení hodnoty z pákového ovladače pro intenzitu
  int vryValue = analogRead(vryPin);
  intensity = map(vryValue, 0, 1023, 0, 255);
 
  // Nastavíme barvu LED
  if (colorState == 0) { // Zelená
    analogWrite(redPin, 0);
    analogWrite(greenPin, intensity);
    analogWrite(bluePin, 0);
  } else if (colorState == 1) { // Červená
    analogWrite(redPin, intensity);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else if (colorState == 2) { // Modrá
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, intensity);
  }
 
  delay(10); // Krátké zpoždění pro stabilizaci čtení
}