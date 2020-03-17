/*******************Demo for MG-811 Gas Sensor Module V1.1*****************************

Author:  Tiequan Shao: tiequan.shao@sandboxelectronics.com
         Peng Wei:     peng.wei@sandboxelectronics.com

Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
************************************************************************************/

#ifndef MGSensor_h
#define MGSensor_h
#include "arduino.h"

class mgsensor
{
  private:

    float voltaje;
    int mg_pin;
    float ganancia;  
    int numero_muestras;  
    int tiempo_muestreo; 
    float voltaje_airelimpio;   
    float diferencia_voltaje;    
    float CO2curve[3];
    
  public:

    mgsensor(int pin);
    void MGRead(int mg_pin);
    int  MGGetPercentage();

};
#endif
