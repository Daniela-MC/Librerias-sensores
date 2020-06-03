/*******************Demo for MG-811 Gas Sensor Module V1.1*****************************
Support:  Tiequan Shao: tiequan.shao@sandboxelectronics.com
         Peng Wei:     peng.wei@sandboxelectronics.com

Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
************************************************************************************/

#include "MGSensor.h"

mgsensor CO2(4);
 
void setup()
{
    Serial.begin(9600);                                              
}

void loop()
{
    int percentage;
    
    percentage = CO2.MGGetPercentage();
    Serial.print("CO2:");
    if (percentage == -1) {
        Serial.print( "<400" );
    } else {
        Serial.print(percentage);
    }

    Serial.print( "ppm" );  
    Serial.print("\n");

    delay(2000);
}
