
#include "MQSensor.h"

p_oled calibrar;

mqsensor::mqsensor(int pin, int gas)
  {
       mq_pin = pin;
       led = 2;
       rl = 1;
       r0_limpio = 9.83;
       muestras_calibracion = 50;
       espera_calibracion = 500;
       muestras_lectura = 5;
       espera_lectura = 50;
       bandera_gas = gas;

  }

float mqsensor::MQResistanceCalculation(int raw_adc)
 {
    float y = 0;
    y = (rl*(4096-raw_adc)/raw_adc);
    return ( ((float) y * (3/2)));
 }

float mqsensor::MQCalibration()
 {
   pinMode(led,OUTPUT);
   digitalWrite(led,HIGH);
   int i, x=0;
   float val=0;
   float r0 = 0;

   for (i=0;i<muestras_calibracion;i++) { 
             
   r0 += MQResistanceCalculation(analogRead(mq_pin));
   if(i%5==0 && i>0){
    calibrar.calibrando(x);
    x++;
   }
   
   delay(espera_calibracion);
  }
  r0 = r0/muestras_calibracion;                   
  r0 = r0/r0_limpio;                        
  digitalWrite(led,LOW);                                                        
  return r0;
 }
 
float mqsensor::MQRead()
 {
    int i;
    rs=0;
    for (i=0;i<muestras_lectura;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(espera_lectura);
  }
    rs = rs/muestras_lectura;
    return rs;
 }

float mqsensor::MQGetGasPercentage(float r0)
 {
    MQRead();
    if ( bandera_gas == 0 ) {
     return MQGetPercentage((rs/r0),LPGCurve);
  } else if ( bandera_gas == 1 ) {
     return MQGetPercentage((rs/r0),COCurve);
  } else if ( bandera_gas == 2 ) {
     return MQGetPercentage((rs/r0),CH4Curve);
  }

 }

float mqsensor::MQGetPercentage(float rs_ro_ratio, float *pcurve)
 {
   return {pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0]))};
 }
