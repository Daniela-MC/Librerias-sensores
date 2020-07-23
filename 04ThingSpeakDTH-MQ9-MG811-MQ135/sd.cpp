
#include "sd.h"

Sd::Sd()
{
  if (!SD.begin(26, 14, 13, 27)) {
    // CS, MOSI, MISO, SCK   
    return;
  }
   
}

void Sd::cabecera()
{
  Datos = SD.open("test.txt", FILE_WRITE);
  
  if (Datos) {
    
    Datos.println("\nAÏrus: Estacion de monitoreo Calidad del Aire");
    Datos.println();
    Datos.flush();
    Datos.close();
  }
}

void Sd::escribir_sd(unsigned long  previousMillis, float number5, float number6, float number9, float number10)
{

  Datos = SD.open("test.txt", FILE_WRITE);
  
  if (Datos) {
    
   
   // Datos.print(dia); Datos.print("/"); Datos.print(mes); Datos.print("/"); Datos.print(ano); Datos.print(",");
    Datos.print(previousMillis); Datos.print(","); 
    Datos.print(number5); Datos.print(",");
    Datos.print(number6); Datos.print(",");
    Datos.print(number9); Datos.print(",");
    Datos.print(number10); Datos.print(",");
   // Datos.print(longitud); Datos.print(",");
   // Datos.print(latitud); Datos.print(",");
   // Datos.print(altitud);
    Datos.println();
    Datos.flush();
    Datos.close();
  }
  
}
