#include "FastLED.h"

#define SEL0 0       //NEED TO FIX
#define SEL1 1       //NEED TO FIX
#define DATA_PIN 3   
#define NUM_LEDS 40  //NEED TO FIX
#define BRIGHTNESS 150

//defs for effects
#define DIVE_SECTIONS 4
// #define debug 1
// #define debugln 1


// #ifdef debug
// debug(str) = Serial.print(str);
// #else
// debug(str);
// #endif

// #ifdef debugln
// debug(str) = Serial.println(str);
// #else
// debugln(str);
// #endif


CRGB leds[NUM_LEDS];

int sel;
int i = 0;  //primary counter
int j = 0;  //sencondar counter

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, INPUT);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
 //Flash blue as intialization
  flash(CRGB::Blue, 250, 1000);
}

void loop() {
  int s0 = digitalRead(SEL0);
  int s1 = digitalRead(SEL1);
  sel = s0 + s1 * 10;

  switch (sel) {
    case 0:  // binary 00 - 0
      startUp();
    case 1:  // binary 01 - 1
      dive();
    case 10:  // binary 10 - 2
      nominalRun();
    case 11:  // binary 11 - 3
      error();
    default:
      leds[i] = CRGB::Blue;
  }
  inc();
  FastLED.show();
  // put your main code here, to run repeatedly:
}

void startUp() {
  // running yellow
  uint8_t yellowIntensity = sin8(j + i * 10);  // Create a phase shift for each LED

  uint8_t red = yellowIntensity;
  uint8_t green = yellowIntensity;
  uint8_t blue = 0;  // No blue for shades of yellow
  if (i % NUM_LEDS / 15 == 0)
    if (j < NUM_LEDS / 15)
      j++;
    else
      j = 0;
  leds[i] = CRGB(red, green, blue);
  delay(20);
}

void dive() {
  //running red
  leds[i] = CRGB::Red;
  for (int k = 0; k < 3; k++) {
    if (i > 1 + k) {
      for (int m = 0; m < DIVE_SECTIONS; m++) {
        if (i / DIVE_SECTIONS < NUM_LEDS / DIVE_SECTIONS)
          leds[i * (m + 1) - k - 1] = CRGB::Black;
      }
    }
  }
  delay(10);
}

void nominalRun() {
  //solid green
  leds[i] = CRGB::Green;
  delay(5);
}

void error() {
  //flashing red
  bool onOff = i % 2 == 0;
  if (onOff) {
    for (int k = 0; k < NUM_LEDS-1; k += 2) {
      leds[k] = CRGB::Red;
      leds[k + 1] = CRGB::Black;
    }
  } else {
    for (int k = 0; k < NUM_LEDS-1; k += 2) {
      leds[k + 1] = CRGB::Red;
      leds[k] = CRGB::Black;
    }
  }

  delay(250);
}


void inc() {
  i++;
  if (i > NUM_LEDS)
    i = 0;
}

void flash(CRGB color, int del, int n){
  Serial.println("flashing");
for (int m = 0; m < n; m++) { 
    for (int k = 0; k < NUM_LEDS; k++) {
      leds[k] = CRGB::Blue;
    }
    digitalWrite(LED_BUILTIN, 255);
    delay(del);
    for (int k = 0; k < NUM_LEDS; k++) {
      leds[k] = CRGB::Black;
    }
    digitalWrite(LED_BUILTIN, 0);
    delay(del);
  }
}
