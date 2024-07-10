#include "clicli.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#define PIN        7
#define NUMPIXELS 38
#define in1 4
#define in2 5
#define enA 3
#define sensorPin 6
#define mp3 8

clicli mycli;  
LiquidCrystal_I2C lcd(0x27,16,2);  
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() { 
  mycli.begin();
  digitalWrite(enA, OUTPUT);
  digitalWrite(in1, OUTPUT);
  digitalWrite(in2, OUTPUT);
  lcd.init();
  lcd.backlight();
  pixels.begin();
  pixels.clear();
 }

void loop() { 
  //neo(0,255,0);
  mycli.run();
  check();
  delay(100);
 }

void moveF(int speed){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed);
}

void check(){
  lcd.clear();
  if(!digitalRead(sensorPin)){ //object close!
    moveF(200);
    message();
    neo(0,255,0);
    lcd.setCursor(0, 0);
    digitalWrite(mp3, HIGH);

    lcd.print("have a blessed day");
    lcd.setCursor(1, 1);
    lcd.print("come again soon!");

  } 
  else {
    moveF(0);
    //neo(255,0,255);
    lcd.setCursor(5, 0);
    lcd.print("WELCOME!");
    lcd.setCursor(3, 1);
    lcd.print("PUT YOUR CUP");
    digitalWrite(mp3, LOW);

    neorun();
  }
}

void message(){
  lcd.setCursor(3,0);
  lcd.print("");
}

void neo(int r, int g, int b){
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(r, g, b));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(10); // Pause before next pass through loop
  }
}
void neorun(){
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0 ,0, 255));
    pixels.setPixelColor(i, pixels.Color(255 ,0, 255));



    pixels.setPixelColor(i-1, pixels.Color(0, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(100); // Pause before next pass through loop
 }
 for(int i=NUMPIXELS; i>0; i--) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0 ,255, 0));
    pixels.setPixelColor(i+1, pixels.Color(0, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(100); // Pause before next pass through loop
 };
}