#include "MQ135.h"

sensor135::sensor135(int pin)
{
  num_pin = pin;
  lec_adc = 0;
  
}

double sensor135::calidad()
{
  lec_adc = analogRead(num_pin);
  return lec_adc;
}
