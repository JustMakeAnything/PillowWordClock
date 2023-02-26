#include <Arduino.h>
void ledSetup();
void ledUpdate();
void setLed(uint16 ledNo);
void ledClear();
uint32_t getStripColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
uint32_t getStripColorHSV(uint16_t h, uint8_t s, uint8_t v);
