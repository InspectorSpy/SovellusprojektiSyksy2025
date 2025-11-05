/*
1. Tee Arduino ohjelma, joka kasvattaa muuttujan arvoa yhdellä, kun arduinon pinniin 2 kytkettyä nappia painetaan ja kasvattaa muuttujan arvoa kymmenellä, kun arduinon pinniin 3 kytkettyä nappia painetaan.
Pääohjelma (loop) tulostaa viiden sekunnin välein  muuttujan arvon sarjamonitorille, ja nollaa muuttujan. (muista volatile!)

*/

#include <Arduino.h>

volatile int muuttuja = 0; // Tällä muutetaan nappien painalluksia
unsigned long edellinenAika = 0; // Aika edellisestä tulosta

const unsigned long viive = 5000; // 5 sek

uint8_t nappi1Pinni = 2; // Pinni nappi 1
uint8_t nappi2Pinni = 3; // Pinni nappi 2

uint8_t nappi1Arvo = 0; // Oletusarvo kun ei painettu
uint8_t nappi2Arvo = 0; // Oletusarvo kun ei painettu

volatile unsigned long viimeisinKeskeytys1 = 0; // Keskeytysaika
volatile unsigned long viimeisinKeskeytys2 = 0; // Keskeytysaika

const unsigned long debounce = 100; // Debounce muuttuja ms

void setup() {
    Serial.begin(9600);

    pinMode(nappi1Pinni, INPUT_PULLUP); // Määritys
    pinMode(nappi2Pinni, INPUT_PULLUP); // Määritys

    attachInterrupt(digitalPinToInterrupt(nappi1Pinni), ISR_nappi1, FALLING); // Keskeytys napille 1, FALLING on painallus
    attachInterrupt(digitalPinToInterrupt(nappi2Pinni), ISR_nappi2, FALLING); // Keskeytys napille 2

    // edellinenAika = millis(); // Alustetaan edellinen aika
}

void ISR_nappi1() { // Keskeytys napille 1
    unsigned long nykyAika = millis();
    if (nykyAika - viimeisinKeskeytys1 > debounce) { // Debounce tarkistus
        muuttuja += 1; // Kasvatetaan muuttujaa yhdellä
        viimeisinKeskeytys1 = nykyAika; // Päivitetään viimeisin keskeytysaika
    }
}

void ISR_nappi2() { // keskeytys napille 2
    unsigned long nykyAika = millis(); 
    if (nykyAika - viimeisinKeskeytys2 > debounce) { // Debounce tarkistus
        muuttuja += 10; // Kasvatetaan muuttujaa kymmenellä
        viimeisinKeskeytys2 = nykyAika; // Päivitetään viimeisin keskeytysaika
    }
}

void loop() {
    unsigned long nykyAika = millis();
    if (nykyAika - edellinenAika >= viive) { // Viiveen tarkastus
        edellinenAika = nykyAika; // Päivitetään edellinen aika nykyiseen
        Serial.print("Muuttuja: ");
        Serial.println(muuttuja);
        muuttuja = 0; // Muuttujan nollaus
    }
}