/*Support:  Tiequan Shao: support[at]sandboxelectronics.com
Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)*/

#include "MQSensor.h"
#define CH4 (0)
#define CO (1)
#define LPG (2)

mqsensor mq_co(34,CH4);
mqsensor mq_ch4(34,CO);
mqsensor mq_lpg(34,LPG);

float Ro;
float co;
float ch4;
float lpg;


void setup() {
  pinMode (2,OUTPUT);
  Serial.begin(9600);                              
  Serial.print("Calibrating...\n");
  Ro = mq_ch4.MQCalibration();
  Serial.print("Calibracion completa...\n");
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.println("kohm");
  Serial.println("--------------------------------------------------------------------------------------------");
  Serial.print("\n\n");
}

void loop() {

  ch4 = mq_ch4.MQGetGasPercentage(Ro);
  co = mq_co.MQGetGasPercentage(Ro);
  lpg = mq_lpg.MQGetGasPercentage(Ro);

  if(ch4 > 200 || co > 200 || lpg > 200 )
  {
    digitalWrite(2,HIGH);
  }
  else 
  {
    digitalWrite(2,LOW);
  }
  Serial.println("----------------------------------------------------------------------------------------------");
  Serial.print("CH4: ");
  Serial.print(ch4);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  Serial.print("CO: ");
  Serial.print(co);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  Serial.print("LPG: ");
  Serial.print(lpg);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  delay (2000);

  

}
