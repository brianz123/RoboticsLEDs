/***
 * 00 - Nominal run
 * 01 - Dive
 * 10 - Startup
 * 11 - Error
 * 
 * 
 */

#include "FastLED.h"

#define SEL0 2  //NEED TO FIX
#define SEL1 3  //NEED TO FIX
#define DATA_PIN 6
#define NUM_LEDS 6  //NEED TO FIX
#define BRIGHTNESS 255

//defs for effects
#define DIVE_SECTIONS 4

CRGB leds[NUM_LEDS];
int time;
int sel;
int i = 0;  //primary counter
int j = 0;  //sencondar counter
bool upDown = true;


void setup() {
  // put your setup code here, to run once:
  time = millis();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, INPUT);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //Flash blue as intialization
  for (int k = 0; k < 255; k += 15) {
    for (i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(k, 255, 255);
    }
    delay(150);
    FastLED.show();
  }
  flash(CRGB::Black, 10,1);
  delay(500);
}


void loop() {
  int s0 = digitalRead(SEL0);
  int s1 = digitalRead(SEL1);
  sel = s0 + s1 * 10;
  // Serial.print("Selction val is: ");
  // Serial.println(sel);
  switch (sel) {
    case 0:  // binary 00 - 0
      nominalRun();
      break;
    case 1:  // binary 01 - 1
      dive();
      break;
    case 10:  // binary 10 - 2 
      // startUp();
      nominalRun();
      break;
    case 11:  // binary 11 - 3
      error();
      break;
    default:
      leds[i] = CRGB::Blue;
  }
  inc();
  // FastLED.show();
  // put your main code here, to run repeatedly:
}

void startUp() {
  // running yellow
  for (int k = 0; k < NUM_LEDS; k++) {
    leds[k] = CRGB::Green;
    leds[i].setHue(j);
  }

  if (j < NUM_LEDS)
    j++;
  else
    j = 0;
  delay(150);
  FastLED.show();
}

void dive() {
  //running Red/Blue
  Serial.println("diving");
  flash(CRGB(255, 50, 0), 100, 1);
  }

void nominalRun() {
  //solid green
  // if(millis()-time >3000){
  //   for(int k = 0; k < NUM_LEDS; k++){
  //     leds[i].fadeToBlackBy(uint8_t fadefactor)
  //   }
  // }
  Serial.println("Nominal Run");
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
    FastLED.show();
  }
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
