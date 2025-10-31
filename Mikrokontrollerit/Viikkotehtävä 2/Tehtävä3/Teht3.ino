/*
Tee aliohjelma, joka lukee Arduinon digitaalipinnien 2-5 tilat ja palauttaa 0/1 tiedon kustakin pinnistä structin avulla tai taulukon osoitteen (pointterin) avulla.
Testaa ohjelmasi oikea toiminta kytkemällä 0 V hyppylangalla 0-3 pinneihin hyppylangan paikkaa vaihtelemalla.
Huom: Määrittele pinnit 0-3 pinMode(x,INPUT_PULLUP), missä x on 2,3,4,5. Vihje seuraavalla kalvolla!
*/

#include <Arduino.h>

struct digitaaliPinnit { // Tehtävän annossa annettu vihje structin käytöstä
    byte pin2;
    byte pin3;
    byte pin4;
    byte pin5;
};

digitaaliPinnit selvitaPinnienTilat1(); // Proto aliohjelmalle
void selvitaPinnienTilat2(int *);

void setup() {
    Serial.begin(9600);
    for (int i = 2; i <= 5; i++) { // INPUT_PULLUP määrittely pinneille 2-5
        pinMode(i, INPUT_PULLUP); // Mitä on INPUT_PULLUP? // Sisäinen vastuksen kytkentä ylöspäin
    }                               // https://deepbluembedded.com/arduino-pinmode-function-input-pullup-pulldown/
}

void loop() {
    digitaaliPinnit tilat = selvitaPinnienTilat1(); // Kutsutaan structia
    Serial.print("Struct method - pin2: "); // Nämä tulostaa pinnien tilat structilla
    Serial.print(tilat.pin2);
    Serial.print(", pin3: ");
    Serial.print(tilat.pin3);
    Serial.print(", pin4: ");
    Serial.print(tilat.pin4);
    Serial.print(", pin5: ");
    Serial.print(tilat.pin5);
    Serial.println();

    int pinArray[4]; // Taulukko pinneille 2-5
    selvitaPinnienTilat2(pinArray); // Kutsuu taulukkoa
    Serial.print("Array method - pin2: "); // Nämä tulostaa pinnien tilat taulukolla
    Serial.print(pinArray[0]);
    Serial.print(", pin3: ");
    Serial.print(pinArray[1]);
    Serial.print(", pin4: ");
    Serial.print(pinArray[2]);
    Serial.print(", pin5: ");
    Serial.print(pinArray[3]);
    Serial.println();

    delay(1000);
}

digitaaliPinnit selvitaPinnienTilat1() { // Structin aliohjelma
    digitaaliPinnit tilat; // muuttuja
    tilat.pin2 = digitalRead(2); // Luetaan pinnien tilat
    tilat.pin3 = digitalRead(3);
    tilat.pin4 = digitalRead(4);
    tilat.pin5 = digitalRead(5);
    return tilat;
}

void selvitaPinnienTilat2(int *pinnit) { // Taulukon aliohjelma
    pinnit[0] = digitalRead(2); // Luetaan pinnien tilat
    pinnit[1] = digitalRead(3);
    pinnit[2] = digitalRead(4);
    pinnit[3] = digitalRead(5);
}