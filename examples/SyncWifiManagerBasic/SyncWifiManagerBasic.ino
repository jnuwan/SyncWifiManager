#include "SyncWifiManager.h"

SyncWifiManager wm;

void setup() {
  wm.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}
