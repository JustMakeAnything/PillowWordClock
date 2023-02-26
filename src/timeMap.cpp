#include <Arduino.h>
#include <constants.h>
#include <timeMap.h>
#include <NTPClient.h>
#include <ledMap.h>

void mapTimeToLed(NTPClient timeClient)
{
    //    Serial.print("Hour : ");
    //    Serial.println(hour);

    // Encode minutes
    uint nexthour = 0;
//    timeClient.setTimeOffset(TIMEZONE);
    uint8 minute = timeClient.getMinutes();
    uint8 minutehigh = minute / 5;
    if (minutehigh >= 5){
        nexthour++;
    }
    if (LAPSESPEED == 0){
        // Shift by 2.5 Minutes to be more accurate
        timeClient.setTimeOffset(TIMEZONE + 150);
    }
    minute = timeClient.getMinutes();
    if (LAPSESPEED == 0){
        timeClient.setTimeOffset(TIMEZONE);
    }
    uint8 minutelow = minute % 5;
    minutehigh = minute / 5;
    switch (minutelow){
    case 0:
        setIstWarWird(1);
        break;
    case 1:
    case 2:
    case 3:
        setIstWarWird(0);
        break;
    case 4:
        setIstWarWird(-1);
        break;
    }
    switch (minutehigh){
    case 0:  // 0-4
        break;
    case 1:  // 5
    case 2:  // 10
    case 3:  // 15
    case 4:  // 20
        setMinutes(minutehigh);
        setNach();
        break;
    case 5:  // 25
        setMinutes(1);
        setHalb();
        setVor();
        break;
    case 6:  // 30
        setHalb();
        break;
    case 7:  // 35
        setMinutes(1);
        setHalb();
        setNach();
        break;
    case 8:   // 40
    case 9:   // 45
    case 10:  // 50
    case 11:  // 55
        setMinutes(12 - minutehigh);
        setVor();
        break;
    default:
        break;
    }

    uint8 hour = timeClient.getHours();
    hour += nexthour;
    if (hour > 12)
    {
        hour -= 12;
    }
    setHour(hour);
    if (hour == 1){
        // No Uhr
    }else{
        setUhr();
    }
}