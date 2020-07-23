#ifndef MQ135_h
#define MQ135_h
#include "arduino.h"

class sensor135
{
  private:

  int num_pin;
  float lec_adc;


  public:

  sensor135(int pin);
  double calidad();
  
};
#endif
