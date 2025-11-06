/*
2. Tee Arduino ohjelma, joka hyödyntää PinChange keskeytyksiä.
Valitaan 8 bitin väylästä aktiiviseksi 5 pinniä ja keskeytyspalvelijan tulee tulostaa hyppylangalla maadoitettaessa keskeyttävän pinnin numero.
Tehtävää helpottamaan on laitettu tunnilla läpikäyty esimerkkikoodi
*/

#include <Arduino.h>

volatile int pcint0PinLow = 0;

void setup() {
  for(int i = 8;i<14;i++)
  {
    pinMode(i,INPUT_PULLUP);  // Arduino pinnit 8-14 INPUT_PULLUP tilaan
  }

  PCICR = 0x01;               // aktivoidaan PCINT0 Portti B antaa vain keskeytyksiä portit C ja D disabloituina 
  //PCICR = B00000001;
  PCMSK0 = B00000011;         // 0x03;  // Enable pins 8 an 9


  Serial.begin(9600);
  interrupts();               // Keskeytykset enabloituna CPU:sta.
}

void loop() {

  if(pcint0PinLow !=0)
  {
    Serial.print("PCINT0 vaylasta keskeytys pinnista HIGH to LOW = ");
    Serial.println(pcint0PinLow);
    pcint0PinLow = 0;
  }
}

ISR(PCINT0_vect) {
  // Joku pinneista D8 - D13 on muuttanut tilaansa 1:sta 0 tai 0 ykkoseen selvitetaan mika pinni
  for(int i = 8;i<10;i++)
  {
    byte luettu = digitalRead(i);
    
    /*while(digitalRead(i)==LOW)
    {
      //odotellaan, etta kayttaja nostaa napin
    }*/

    if(luettu==LOW)
    {
      pcint0PinLow = i;
    }

  }  
}

ISR(PCINT1_vect) {
  // This function will be called when a pin change interrupt occurs on pin 2
  Serial.println("interrupt 1");
}

ISR(PCINT2_vect) {
  // This function will be called when a pin change interrupt occurs on pin 2
  Serial.println("interrupt 2");
}
