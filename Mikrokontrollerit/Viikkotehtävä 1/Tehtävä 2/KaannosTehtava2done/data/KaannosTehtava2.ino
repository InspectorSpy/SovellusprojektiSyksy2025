#include "esimerkkiheader.h"

void setup() {
  Serial.begin(BAUDINOPEUS);
}

void loop() {
  while(1)
  {
    Serial.println("Give first number");
    while(Serial.available()==0)
    {
      // let's just wait until user gives number
      int foo = 0;
    }
    long foo = Serial.parseInt();

    Serial.println("And give now second number");
    while(Serial.available()==0)
    {
      // let's just wait until user gives number
      int bar = 0;
    }
    long bar = Serial.parseInt();

    Serial.println("And give operation +,-,* or / you want to make");
    while(Serial.available()==0)
    {
      // let's just wait until user gives number
    }
    char operation = Serial.read();

    Serial.print(foo);
    Serial.print(" + ");
    Serial.print(bar);
    Serial.print(" = ");
    Serial.println(aliohjelma(foo,bar,operation));   
  } // end of while
}   // end of loop()
  
