
#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

p_oled::p_oled()
{
   display.begin(SSD1306_SWITCHCAPVCC); 
}

/*Dibuja el logo de AÏrus, el cual debe pasarse en mapa de bits*/
void p_oled::iniciar_pantalla()
{
  display.clearDisplay(); //Siempre hay que limpiar la pantalla para escribir 
  display.drawBitmap(0, 0, logo_bmp, 128, 64, WHITE); //Dibujo de la imagen del mapa de bits
  display.display();
}

/*Escribe texto en la pantalla, tam indica el tamaño de la letra. Puede tomar valores desde 1 hasta 5. Pos indica la posicion que tendra 
 *el texto en la pantalla. Este se refiere a la posicion en y (rango 0-64). String es el texto que se desea imprimir.
 */
void p_oled::mostrar_texto (int tam, int pos, String text)
{
  
  display.clearDisplay();
  display.setTextSize(tam);
  display.setTextColor(WHITE);
  display.setCursor(0,pos);
  display.println(text);
  display.display();
}

/*Anima los textos mostrados en la pantalla, r (right) indica movimiento a la derecha, l (left) indica movimiento a la izquierda*/ 
void p_oled::iniciar_movimiento(char direccion)
{
    if(direccion=='r')
    {
      display.startscrollright(0x00, 0x0F);
    }

    else 
    {
      display.startscrollleft(0x00, 0x0F);
    }
}

/*Detiene la animacion del texto*/
void p_oled::detener_movimiento()
{
  display.stopscroll();
}

/*Imprime en pantalla cada una de las variables sensadas*/
void p_oled::mostrar_variable(float number1, float number2, float number3,float number4, float number5, float number6, float number7, float number8) 
{
  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("CO="); display.print(number1); display.println("ppm");  //Impresion de las variables con sus unidades en la pantalla
  display.print("CO2=");display.print(number2); display.println("ppm");
  display.print("CH4=");display.print(number3); display.println("ppm");
  display.print("LPG=");display.print(number4); display.println("ppm");
  display.print("Temp=");display.print(number5);display.write(167); display.println("C");
  display.print("Hum=");display.print(number6); display.println("%");
  display.print("CA="); display.print(number7); display.println("ppm");
  display.print("CA="); display.print(number8); display.println("ppm");
  display.display();
}

/*Presentacion del logo de AÏrus con la barra de carga para la calibracion*/
void p_oled::calibrando(int algo)
{
  Serial.println(algo);
  display.clearDisplay();
  if (algo == 0){
    display.drawBitmap(0, 0, logo1, 128, 64, WHITE); 
  }
  else if (algo == 1){
    display.drawBitmap(0, 0, logo2, 128, 64, WHITE); 
  }
   else if (algo == 2){
    display.drawBitmap(0, 0, logo3, 128, 64, WHITE); 
  }
   else if (algo == 3){
    display.drawBitmap(0, 0, logo4, 128, 64, WHITE); 
  }
   else if (algo == 4){
    display.drawBitmap(0, 0, logo5, 128, 64, WHITE); 
  }
   else if (algo == 5){
    display.drawBitmap(0, 0, logo6, 128, 64, WHITE); 
  }
   else if (algo == 6){
    display.drawBitmap(0, 0, logo7, 128, 64, WHITE); 
  }
   else if (algo == 7){
    display.drawBitmap(0, 0, logo8, 128, 64, WHITE); 
  } 
  else if (algo == 8){
    display.drawBitmap(0, 0, logo9, 128, 64, WHITE); 
  }
   /*else if (algo == 9){
    display.drawBitmap(0, 0, logo9, 128, 64, WHITE); 
  }*/
  
  display.display();
    
}
