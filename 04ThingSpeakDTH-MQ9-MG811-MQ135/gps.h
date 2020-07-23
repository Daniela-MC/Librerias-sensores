
#ifndef gps_h
#define gps_h
#include "arduino.h"
#include <TinyGPS++.h> 
#include <HardwareSerial.h> 


class Gps
{
 
  
  public: 

  Gps();
  double obtener_longitud();
  double obtener_latitud();
  double obtener_altitud();
  double obtener_dia();
  double obtener_mes();
  double obtener_ano();

  
};



#endif
