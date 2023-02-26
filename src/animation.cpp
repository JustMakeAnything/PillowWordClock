#include <Arduino.h>
#include <constants.h>
#include <animation.h>
#include <ledMap.h>
#include <led.h>

enum states {background, timestate};
enum animations {animOff, animGreenBlue, animPulse, animForegroundPulse};

uint16_t pause = 0;
int16_t phase = 0;
uint32_t count = 0;
uint8_t state = background;
//uint8_t animation = animForegroundPulse;  // animPulse;  // animGreenBlue;
uint8_t animation = animForegroundPulse;

#define PULSESIZE 5

void animate(){
    state = background;
    // set a background effect
    for (int16_t i = 0; i < LED_COUNT; i++){
        setValidLed(i);
    }
    state = timestate;

    switch (animation){
    case animPulse:
    case animForegroundPulse:
        if (pause > 0){
            pause--;
            phase = 0;
        }else{
            if (phase == LED_COUNT+PULSESIZE){
                pause = 100;
            }
        }
        break;
    default:  // animOff
        break;
    }
    phase++;
    count++;
    return;
}


uint32_t getColor(int ledNumber){
    switch (state){
    case timestate:
        switch (animation){
            case animForegroundPulse:
                {
                    if (pause > 1){
                        return getStripColorHSV(count>>8, 255, 255);
                    }
                    uint8_t distance = abs(ledNumber+PULSESIZE*2 - phase);
                    if (distance > PULSESIZE*2){
                        return getStripColorHSV(count>>8, 255, 255);
                    }
                    return getStripColorHSV((count>>8)+((PULSESIZE*2)-distance)*1300,
                                             255, distance*(100/(PULSESIZE*2))+150);
                }
            default:  // animOff
                return getStripColorHSV(count>>8, 255, 255);
        }
    case background:
        switch (animation){
            case animGreenBlue:
                return getStripColor(0, 20, (ledNumber*2+phase)%20, 0);
            case animPulse:
                {
                    if (pause > 1){
                        return  getStripColor(0, 0, 0, 0);
                    }
                    uint8_t distance = abs(ledNumber - phase);
                    if (distance > PULSESIZE){
                        return getStripColor(0, 0, 0, 0);
                    }
                    return getStripColorHSV(22000+phase*100+count*10, 255, 150-distance*(140/PULSESIZE));
                }
            default:  // animOff
                return getStripColor(0, 0, 0, 0);
        }
        break;
    default:
        break;
    }
    return getStripColorHSV(0, 0, 0);
}