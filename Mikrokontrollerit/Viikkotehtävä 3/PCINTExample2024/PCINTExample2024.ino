/*
1. Tee Arduino ohjelma, joka kasvattaa muuttujan arvoa yhdellä, kun arduinon pinniin 2 kytkettyä nappia painetaan ja kasvattaa muuttujan arvoa kymmenellä, kun arduinon pinniin 3 kytkettyä nappia painetaan. Pääohjelma (loop) tulostaa viiden sekunnin välein  muuttujan arvon sarjamonitorille, ja nollaa muuttujan. (muista volatile!)

2. Tee Arduino ohjelma, joka hyödyntää PinChange keskeytyksiä. Valitaan 8 bitin väylästä aktiiviseksi 5 pinniä ja keskeytyspalvelijan tulee tulostaa hyppylangalla maadoitettaessa keskeyttävän pinnin numero. Tehtävää helpottamaan on laitettu tunnilla läpikäyty esimerkkikoodi

3. (VAPAAEHTOINEN EXTRA TEHTÄVÄ): Tee pelin aihio. Peli käynnistyy lähettämällä sarjaporttiin merkki 's'. Pelin ollessa käynnissä ohjelma arpoo kahden sekunnin välein numeron 1,2,3 tai 4 ja tulostaa sen kometoriville. Käyttäjän tulee kytkeä numeroa vastaava pinni maahan ennen kuin seuraava numero arvotaan. Peli jatkuu kunnes käyttäjä kytkee väärän pinnin, tai ei ehdi ajoissa. Lopuksi tulostetaan kometoriville onnnistuneiden painallusten määrä. Pelin voi aloittaa alusta kirjoittamalla uudenstaan merkki 's' sarjaporttiin.
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
