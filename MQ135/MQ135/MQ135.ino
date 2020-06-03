#include "MQ135.h"

sensor135 sensor(27);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  sensor.calidad();
  delay(250);
}
