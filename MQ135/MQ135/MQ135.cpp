#include "MQ135.h"

sensor135::sensor135(int pin)
{
  num_pin = pin;
  lec_adc = 0;
  
}

void sensor135::calidad()
{
  lec_adc = analogRead(num_pin);
  Serial.println(lec_adc, DEC);
  Serial.println("ppm");

  if(lec_adc<=300)
  {
    Serial.println("Aire Limpio");
  }
  else
  {
    Serial.println("Aire Contaminado");
  }
  
}
