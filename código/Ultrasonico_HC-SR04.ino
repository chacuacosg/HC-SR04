/*
  Conexiones HC-SR04
  VCC   Arduino 5v
  GND   Arduino GND
  ECHO  Arduino pin 6
  TRIG  Arduino pin 7
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define P_echo 6
#define P_trig 7
long duracion, distancia;

void setup() {

  Serial.begin(9600);
  pinMode(P_echo, INPUT);
  pinMode(P_trig, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  digitalWrite(P_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(P_trig, HIGH);   //GENERA UN PULSO DE TRIGER POR 10ms
  delayMicroseconds(10);
  digitalWrite(P_trig, LOW);

  duracion = pulseIn(P_echo, HIGH);
  distancia = (duracion / 2) / 29;    //CALCULA LA DISTANCIA EN cm

  if (distancia >= 500 || distancia <= 0) { //SI DISTANCIA ES MAYOR A 500cm Y MENOR DE 0cm
    Serial.println("---");
  }
  else {
    Serial.print(distancia);  //ENTONCES SI DISTANCIA ES MENOR A 500cm Y MAYOR A 0cm
    Serial.println(" cm");    //NOS MOSTRARA EN EL MONITOR SERIAL LA DISTANCIA MEDIDA
    digitalWrite(13, LOW);    //EL LED PERMANECERA APAGADO
  }
  if (distancia <= 10 && distancia >= 1) {  //SI LA DISTANCIA ES MENOR A 10cm
    digitalWrite(13, HIGH);                 //ENCIENDE EL LED Y NOS MUESTRA UN MSG DE
    Serial.println("Alamra......");         //ALARMA
  }
  delay(400);
}
