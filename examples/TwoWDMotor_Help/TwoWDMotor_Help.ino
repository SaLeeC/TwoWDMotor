/*
 * TwoWDMotor TEST
 * 
 * Call the help function and explain the contents
 * of the library
 * Use the serial console
 * 
 */

#include <TwoWDMotor.h>

//crea l'oggetto motori associandogli i piedini dal 2 al 5
TwoWDMotor motori(2,3,4,5);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  //chiama la funzione Help della libreria
  motori.Help(Serial);
  delay(10000);
}
