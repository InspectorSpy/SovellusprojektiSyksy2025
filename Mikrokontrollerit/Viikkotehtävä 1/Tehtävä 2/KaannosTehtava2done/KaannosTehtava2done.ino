#include "aliohjelmat.h"

void setup() {
  Serial.begin(BAUDINOPEUS);
  Serial.setTimeout(10000); // Annettu käyttäjälle aikaa syöttää
}

void tyhjenna_bufferi() {
  while(Serial.available() != 0) // tyhjennetään bufferi aina parseIntin jälkeen
  char t = Serial.read();
}

void loop() { // poistettu ylin while loop

    tyhjenna_bufferi(); // Tyhjennetään bufferi
    
    Serial.println("Give first number");
    int foo = 0; // siirretty int foo = 0; tähän while loopin sisältä
    while(Serial.available()==0)
    {
      // let's just wait until user gives number
    }
    foo = Serial.parseInt(); 

    tyhjenna_bufferi(); // Tyhjennetään bufferi

    Serial.println("And give now second number");
    int bar = 0; // siirretty int bar = 0; tähän while loopin sisältä
    while(Serial.available()==0)
    {
      // let's just wait until user gives number
    }
    bar = Serial.parseInt();

    tyhjenna_bufferi(); // Tyhjennetään bufferi

    Serial.println("And give operation +,-,* or / you want to make");
    while(Serial.available()==0)
    {
      // let's just wait until user gives number
    }
    char operation = Serial.read();

    Serial.print(foo);
    Serial.print(" ");
    Serial.print(operation); // lisätty operation printiksi, jotta +, -+ * ja / tunnistuu
    Serial.print(" ");
    Serial.print(bar);
    Serial.print(" = ");
    Serial.println(aliohjelma(foo,bar,operation));

    tyhjenna_bufferi(); 
}   // end of loop()
  
