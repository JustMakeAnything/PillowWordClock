#include <Arduino.h>
#include <constants.h>
#include <ledMap.h>
#include <led.h>

// See constants.h for LED maps
int elements[ELEMENTS] = ELEMENTMAP;

void setElement(uint8 number){
    uint16 start = 0;
    for (uint8 elementNo = 0; elementNo < number; elementNo++){
        start += elements[elementNo];
    }
    for (uint16 ledNo = 0; ledNo < elements[number]; ledNo++){
        setLed(start+ledNo);
    }
}

void setValidLed(uint16_t ledNumber){
    uint16_t currentElementLedCount = elements[0];
    uint8_t elementNo = 0;
    while (currentElementLedCount <= ledNumber){
        elementNo++;
        currentElementLedCount += elements[elementNo];
    }
    // Serial.print("elementNo : ");
    // Serial.print(elementNo);
    // Serial.print("value : ");
    // Serial.print(elements[elementNo]);
    if (elements[elementNo] > 1){
        // Gaps with one LED are never shown
        setLed(ledNumber);
    }else{
        // Serial.print("led : ");
        // Serial.println(ledNumber);
    }
}

void setAllOff(){
    ledClear();
}

void setHour(uint8 hour){
    uint8 hours[12] = HOURMAP;
    if ( hour <1 || hour > 12 ){
        return;
    }
    setElement(hours[hour-1]);
}
void setUhr(){
    setElement(OCLOCK);
}

void setEs(){
    setElement(0);
}
void setHalb(){
    setElement(11);
}
void setIstWarWird(int8 was){
    // -1 0 1
    if (abs(was) > 1){
        was = 0;
    }
    uint8 istWarWird[3] = {3, 1, 2};
    setElement(istWarWird[was+1]);
}

void setVor(){
    setElement(TO);
}
void setNach(){
    setElement(PAST);
}

void setMinutes(uint minute){
    // Minutes : x, 5, 10, 15, 20, x
    uint8 minutes[4] = MINUTEMAP;
    if ( minute <1 || minute > 4 ){
        return;
    }
    setElement(minutes[minute-1]);
}

