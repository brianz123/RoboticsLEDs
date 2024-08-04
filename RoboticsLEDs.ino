#include <FastLED.h>

#define sel0 0        //NEED TO FIX
#define sel1 1        //NEED TO FIX
#define LED_PIN 3     //NEED TO FIX
#define NUM_LEDS 300  //NEED TO FIX


CRGB leds[NUM_LEDS];

int sel[2];
int i = 0;
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  sel = { digitalRead(sel0), digitalRead(sel1) };

  switch (sel) {
    case { 0, 0 }:
      startup();
    case { 0, 1 }:
      dive();
    case { 1, 0 }:
      nominalRun();
    case { 1, 1 }:
      error();
  }
  FastLED.show();
  // put your main code here, to run repeatedly:
}

void startUp() {
// running yellow
}

void dive() {
 //running red 
}

void nominalRun() {
//solid green
}

void error() {
//flashing red
}


void inc() {
  i++;
  if (i > NUM_LEDS)
    i = 0;
}