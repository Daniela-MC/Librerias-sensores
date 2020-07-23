#ifndef sd_h
#define sd_h
#include "arduino.h"
#include <mySD.h>

class Sd
{

  private:

  File Datos;
  
  public:

  Sd();
  void cabecera();
  void escribir_sd(unsigned long  previousMillis, float number5, float number6, float number9, float number10);
};

#endif
