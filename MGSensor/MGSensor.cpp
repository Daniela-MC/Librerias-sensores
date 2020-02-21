/*******************Demo for MG-811 Gas Sensor Module V1.1*****************************

Author:  Tiequan Shao: tiequan.shao@sandboxelectronics.com
         Peng Wei:     peng.wei@sandboxelectronics.com

Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
************************************************************************************/
#include "MGSensor.h"

mgsensor::mgsensor(int pin)
  {
    mg_pin = pin;
    ganancia = 5.7;
    numero_muestras = 50;
    tiempo_muestreo = 5;
    voltaje_airelimpio = 0.170;  // log(400)
    diferencia_voltaje = 0.20; // dos puntos de la grafica en el eje y
    CO2curve[0] = 2.602;
    CO2curve[1] = 0.170;
    CO2curve[2] = (0.20/(2.602-3));   
  }

void mgsensor::MGRead(int mg_pin)
{
    int i;
     voltaje = 0.0;

    for (i=0;i<numero_muestras;i++) {
        voltaje += analogRead(mg_pin);
        delay(tiempo_muestreo);
    }
    voltaje = (voltaje/numero_muestras) *3.3/4096.0 ;
      
}

int  mgsensor::MGGetPercentage()
{
  MGRead(mg_pin);

  
   if ((voltaje/ganancia )>=voltaje_airelimpio) {
      return -1;
   } else { 
      return pow(10, ((voltaje/ganancia)-CO2curve[1])/CO2curve[2]+CO2curve[0]);
   }
}
