/*
Prueba de integración del nodo de Airus
Fecha: 29/05/2020
Autor: César Alvarez
Prueba: 04 ThingSpeaK + DHT + MQ9 + MG811 + MQ135
*/

//Librerias
#include "ThingSpeak.h"
#include "secrets.h"
#include <WiFi.h>
#include "DHT.h"
#include "MQSensor.h"
#include "MGSensor.h"
#include "oled.h"
#include "gps.h"
#include "sd.h"
#include "MQ135.h"


//Definiciones de los pines a usar y sus configuraciones                     

//Definicion de los pines a usar en los sensores
#define DHTPIN 19//DHT Sensor de humedad y temperatura
#define DHTTYPE DHT11 //Define el tipo de sensor DHT 11
#define TAZAACTUALIZACIONNODO 1500 //2s 
#define MQ9PIN 36 //Sensor MQ9
#define MG811IN 39 //Sensor MG811
#define MQ135PIN 35 //Sensor MQ135
#define CH4 (0) //Tipo de Gas a medir - CH4
#define CO (1) //Tipo de Gas a medir - CO
#define LPG (2) //Tipo de Gas a medir - LPG
#define NH3 (0) //Tipo de Gas a medir - NH3
#define NOx (1) //Tipo de Gas a medir - NOx
#define ALCOHOL (2) //Tipo de Gas a medir - Alcohol                      

//Declaracion de los objetos usados
DHT dht(DHTPIN,DHTTYPE);//Objeto del sensor DHT
mqsensor MQ9_co(MQ9PIN,CH4);
mqsensor MQ9_ch4(MQ9PIN,CO);
mqsensor MQ9_lpg(MQ9PIN,LPG);
mgsensor MG811_CO2(MG811IN);
sensor135 sensor(35);
//mqsensor MQ135_NH3(MQ135PIN,NH3);
//mqsensor MQ135_NOx(MQ135PIN,NOx);
//mqsensor MQ135_Alcohol(MQ135PIN,ALCOHOL);
p_oled control; //Objeto para el control de la pantalla
Gps ubicacion; //Objeto para el GPS
Sd memoria; //Objeto para la escritura en la memoria SD
//Configuración de la aplicación ThingSpeak
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

//Declaración de variables globales a usar en el nodo
unsigned long previousMillis = 0;
float number1, aux1=0;  // number contiene la variable 
float number2, aux2=0;  // aux contiene los promedios de las mediciones de cada 15s. Estos son enviados a ThingSpeak
float number3, aux3=0; 
float number4, aux4=0; 
float number5, aux5=0; 
float number6, aux6=0; 
float number7, aux7=0; 
float number8, aux8=0; 
float number9;         
float number10;
float longitud;
float latitud;
float altitud;
int dia, mes, ano;
int  datos = 0; //hit = 0;

float mQ9Ro;//Resistencia de calibración para el MQ9
float mQ135Ro;//Resistencia de calibración para el MQ135
String myStatus = "";//Mensaje de estado para ThingSpeak

void setup() {
  //Inicializacion del display de la pantalla 

  control.iniciar_pantalla();
  delay(3000);
  //Inicialización del puerto serial
  Serial.begin(115200);
  //Mensaje de inicio del nodo de Airus
  Serial.println("\nNodo Airus\nSistema de medición\nArranque inicial");
  //Inicialización de los objetos usados
  WiFi.mode(WIFI_STA);//Objeto WiFi   
  ThingSpeak.begin(client);//Objeto ThingSpeak
  //DHT inicialización
  dht.begin();//Objeto Sensor DHT 
  control.mostrar_texto(2, 32, "calibrando");
  control.iniciar_movimiento('r');
  delay(7000);
  control.iniciar_pantalla();
  delay(7000);
 //MQ9 inicializacion
  Serial.print("\nCalibración del MQ9\n");
  mQ9Ro = MQ9_ch4.MQCalibration();
  Serial.print("Calibracion completa del MQ9...\n");
  Serial.print("MQ9 Ro=");
  Serial.print(mQ9Ro);
  Serial.println("kohm");
  delay(2000);
  memoria.cabecera();
/*  Serial.print("\nCalibración del MQ135\n");
  mQ135Ro = MQ135_NH3.MQCalibration();
  Serial.print("Calibracion completa del MQ135...\n");
  Serial.print("MQ135 Ro=");
  Serial.print(mQ135Ro);
  Serial.println("kohm");*/
  delay(1000);
}

void loop() {

  // Conexión al WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("\nConectado a la red SSID: ");
    Serial.println(SECRET_SSID);
    control.mostrar_texto(1, 32, "Conexion\nEstablecida");
    control.iniciar_movimiento('r');
    delay(4000);
    control.detener_movimiento();
    delay(1000);
    control.iniciar_movimiento('l');
    delay(4000);
    control.mostrar_texto(2, 32, SECRET_SSID);
  while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConectado.");
  }
  
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= TAZAACTUALIZACIONNODO) {
    previousMillis = currentMillis;
    
  //Lectura de los sensores conectados
  number1=MQ9_co.MQGetGasPercentage(mQ9Ro);//Lectura de Monoxido de Carbono
  number2=MG811_CO2.MGGetPercentage();//Lectara del CO2
  number3=MQ9_ch4.MQGetGasPercentage(mQ9Ro);//Lectura de Metano
  number4=MQ9_lpg.MQGetGasPercentage(mQ9Ro);//Lectura de Gas Licuado de Petroleo
  number5 = dht.readTemperature();//Lectura de temperatura
  number6 = dht.readHumidity();//Lectura de humedad
  //number7= MQ135_NH3.MQGetGasPercentage(mQ135Ro); //Lectura de Amoniaco
  //number8 =MQ135_NOx.MQGetGasPercentage(mQ135Ro); //Lectura de Oxido de nitrogeno
  number7=sensor.calidad();
  number8=analogRead(MQ135PIN);
  longitud=ubicacion.obtener_longitud();
  latitud=ubicacion.obtener_latitud();
  altitud=ubicacion.obtener_altitud();
  dia=ubicacion.obtener_dia();
  mes=ubicacion.obtener_mes();
  ano=ubicacion.obtener_ano(); 
  number9 = analogRead(MQ9PIN);
  number10 = analogRead(MQ135PIN);
  memoria.escribir_sd(previousMillis, number5, number6, number9, number10);
  aux1 += number1;
  aux2 += number2;
  aux3 += number3;
  aux4 += number4;
  aux5 += number5;
  aux6 += number6;
  aux7 += number7;
  aux8 += number8;
  datos ++; 
  }
  
  if(datos==10)
  {
      aux1 = aux1/10;
      aux2 = aux2/10;
      aux3 = aux3/10;
      aux4 = aux4/10;
      aux5 = aux5/10;
      aux6 = aux6/10;
      aux7 = aux7/10;
      aux8 = aux8/10;
      
      control.mostrar_variable(aux1, aux2, aux3, aux4, aux5, aux6, aux7, aux8);
      Serial.print("Longitud = "); Serial.println (longitud,6);
      Serial.print("Latitud = "); Serial.println (latitud,6);
      Serial.print("Altitud = "); Serial.println (altitud,6);
      Serial.print("Fecha = "); Serial.print(dia); Serial.print("/");
      Serial.print(mes); Serial.print("/"); 
      Serial.print(ano); Serial.println();
      //Presentación de la variables a enviar a ThingSpeak>
      ThingSpeak.setField(1, aux1);
      ThingSpeak.setField(2, aux2);
      ThingSpeak.setField(3, aux3);
      ThingSpeak.setField(4, aux4);
      ThingSpeak.setField(5, aux5);
      ThingSpeak.setField(6, aux6);
      ThingSpeak.setField(7, aux7);
      ThingSpeak.setField(8, aux8);

  //Escritura de los valores en la plataforma ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Actualización exitosa del canal.");
  }
  else{
    Serial.println("Problema al actualizar el canal. HTTP error code: " + String(x));
  }
  aux1 = 0;
  aux2 = 0;
  aux3 = 0;
  aux4 = 0;
  aux5 = 0;
  aux6 = 0;
  aux7 = 0;
  aux8 = 0;
  datos = 0;
  }

  if(currentMillis>=3600000)
  {
     control.mostrar_texto(2, 32, "Tiempo cumplido");  
  } 
}
