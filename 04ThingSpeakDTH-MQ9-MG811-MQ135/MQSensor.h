
#ifndef MQSensor_h
#define MQSensor_h
#include "arduino.h"
#include "oled.h"


class mqsensor
{
  private:

    int mq_pin;
    int led;
    int bandera_gas;
    float rl;
    float r0_limpio;
    int muestras_calibracion;
    int espera_calibracion;
    int muestras_lectura;
    int espera_lectura;
    float LPGCurve[3] = {2.3,0.32,-0.49};
    float COCurve[3] = {2.3,0.25,-0.58};
    float CH4Curve[3] = {2.3,0.49,-0.38};
    float rs;

  public:

     mqsensor(int pin, int gas);
    float MQResistanceCalculation(int raw_adc);
    float MQCalibration();
    float MQRead();
    float MQGetGasPercentage(float r0);
    float  MQGetPercentage(float rs_ro_ratio, float *pcurve);
    
};
#endif
