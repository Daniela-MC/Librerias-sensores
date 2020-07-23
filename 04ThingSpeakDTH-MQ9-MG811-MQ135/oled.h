/**************************** Libreria para pantalla OLED con conexion SPI **************************/

#ifndef oled_h
#define oled_h
#include "arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include"airus.h"

#define OLED_MOSI (23)      //SDA
#define OLED_CLK (18)       //SCK
#define OLED_DC (2)         //DC
#define OLED_CS (5)         //CS
#define OLED_RESET (4)      //RES
#define SCREEN_WIDTH (128)
#define SCREEN_HEIGHT (64)



class p_oled{

  
  public:
  
  p_oled();
  void iniciar_pantalla();
  void mostrar_texto (int tam, int pos, String text);
  void iniciar_movimiento(char direccion);
  void detener_movimiento();
  void mostrar_variable(float number1, float number2, float number3,float number4, float number5, float number6, float number7, float number8); 
  void calibrando(int algo);

}; 

 

#endif
