#include "FastLED.h"

#define SEL0 2  //NEED TO FIX
#define SEL1 3    //NEED TO FIX
#define DATA_PIN 6
#define NUM_LEDS 8  //NEED TO FIX
#define BRIGHTNESS 255

//defs for effects
#define DIVE_SECTIONS 4

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
  flash(CRGB::Orange, 250, 3);
}

void loop() {
  int s0 = digitalRead(SEL0);
  int s1 = digitalRead(SEL1);
  sel = s0 + s1 * 10;
  Serial.print("Selction val is: ");
  Serial.println(sel);
  switch (sel) {
    case 0:  // binary 00 - 0
      startUp();
      break;
    case 1:  // binary 01 - 1
      dive();
      break;
    case 10:  // binary 10 - 2
      nominalRun();
      break;
    case 11:  // binary 11 - 3
      error();
      break;
    default:
      leds[i] = CRGB::Blue;
  }
  inc();
  delay(250);
  // FastLED.show();
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
  FastLED.show();
}

void dive() {
  //running Red/Blue
  Serial.println("diving");
  flash(CRGB(255,50,0), 100, 1);
  // for (int k = 0; k < NUM_LEDS; k++) {
  //   leds[k] = CRGB::Blue;
  //   FastLED.show();
  //   delay(100);
  // }
  // digitalWrite(LED_BUILTIN, 255);

  // for (int k = 0; k < NUM_LEDS; k++) {
  //   leds[k] = CRGB::Red;
  //   FastLED.show();
  //   delay(100);
  // }
  // digitalWrite(LED_BUILTIN, 0);
}

void nominalRun() {
  //solid green
  Serial.println("Nominal Run");
  leds[i] = CRGB::Green;
  delay(50);
  FastLED.show();
}

void error() {
  //flashing red
  Serial.println("Error");
  bool onOff = i % 2 == 0;
  if (onOff) {
    for (int k = 0; k < NUM_LEDS - 1; k += 2) {
      leds[k] = CRGB::Red;
      leds[k + 1] = CRGB::Black;
    }
  } else {
    for (int k = 0; k < NUM_LEDS - 1; k += 2) {
      leds[k + 1] = CRGB::Red;
      leds[k] = CRGB::Black;
    }
  }
  FastLED.show();
  delay(250);
}


void inc() {
  i++;
  if (i > NUM_LEDS)
    i = 0;
}

void flash(CRGB color, int del, int n) {
  // Serial.println("flashing");
  for (int m = 0; m < n; m++) {
    for (int k = 0; k < NUM_LEDS; k++) {
      leds[k] = color;
      FastLED.show();
    }
    delay(del);
    for (int k = 0; k < NUM_LEDS; k++) {
      leds[k] = CRGB::Black;
      FastLED.show();
    }
    delay(del);
  }
}
