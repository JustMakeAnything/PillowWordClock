#include <Arduino.h>
#include <led.h>
#include "Adafruit_NeoPixel.h"
#include <constants.h>
#include <animation.h>

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void ledSetup() {
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(50);
}

void ledClear(){
  strip.clear();
}

uint32_t getStripColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w){
  return strip.Color(r, g, b, w);
}
uint32_t getStripColorHSV(uint16_t h, uint8_t s, uint8_t v){
  return strip.ColorHSV(h, s, v);
}


void setLed(uint16 ledNo){
  uint32_t color = getColor(ledNo);
  strip.setPixelColor(ledNo, color);
}

void ledUpdate(){
    strip.show();
}
