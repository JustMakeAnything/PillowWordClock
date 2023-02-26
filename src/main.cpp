#include <Arduino.h>
#include <wifiConnection.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <constants.h>
#include <led.h>
#include <ledMap.h>
#include <timeMap.h>
#include <animation.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  Serial.begin(74880);
  startWifi();
  ledSetup();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  timeClient.update();
  stopWifi();
}

unsigned long previous = 0;
unsigned long timelapse = TIMEZONE;
unsigned long oldTime = 0;
#define DELAYMS 50

void loop() {
  if (oldTime > millis()){
    return;
  }
  oldTime = millis() + DELAYMS;
  setAllOff();
  animate();
  unsigned long now = timeClient.getEpochTime();
  mapTimeToLed(timeClient);
  setEs();
  ledUpdate();

  if (now-previous < IDLEINTERVAL){
    return;
  }
  previous = now+LAPSESPEED;
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);


  timeClient.setTimeOffset(timelapse);
  timelapse += LAPSESPEED;

}