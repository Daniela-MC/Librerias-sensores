
#include "gps.h"

TinyGPSPlus gps; //Declaracion del objeto

HardwareSerial SerialGPS(1); /* ESP 32 admite hasta 3 conexiones seriales. El numero entre parentesis es UART_nr.
                                Esto diferencia las tres posibles conexiones. Este valor puede ser 0,1 o 2*/ 

Gps::Gps()
{
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);  // El modulo GPS tiene una velocidad de transmision predeterminada de 9600. Definicion de pines 16 RX, 17 TX 
}

double Gps::obtener_longitud()
{
  return gps.location.lng();
}

double Gps::obtener_latitud()
{
  return gps.location.lat();
}

double Gps::obtener_altitud()
{
  return gps.altitude.meters();
}

 double Gps::obtener_dia()
{
  return gps.date.day();
}

double Gps::obtener_mes()
{
  return gps.date.month();
}

double Gps::obtener_ano()
{
  return gps.date.year();
}
