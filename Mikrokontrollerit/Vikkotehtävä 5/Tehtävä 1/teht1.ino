/*
1: Tee sekuntikello käyttäen Loop-rakennetta ja Timeria. Sekuntikellon tulee laskea sekunnin kymmenyksiä, sekunteja ja minuutteja

- Sekuntikello käynnistetään maadoittamalla pinni 2 (voit käyttää keskeytyksiä apuna)

- Sekuntikello päivittää ajan sarjaportille sekunnin välein.

- Sekuntikello pysäytetään maadoittamalla pinni 3, jolloin tulostetaan tarkka aika kymmenyksineen, ja nollataan aika uutta ajanottoa varten.
*/

#include <Arduino.h>

uint8_t pinStart = 2; // Pinni sekuntikellon käynnistämiseen
uint8_t pinStop = 3; // Pinni sekuntikellon pysäyttämiseen

volatile bool running = false; // Sekuntikellon tila
volatile bool shouldStop = false; // Sekuntikellon pysäytys

unsigned long startTime = 0; // Ajanotto alkaa tästä
unsigned long lastPrintTime = 0; // Viimeisin tulostus

unsigned int tenths = 0; // Kymmennyksen
unsigned int seconds = 0; // Sekuntit
unsigned int minutes = 0; // Minuutit

void startTimer() { // Sekuntellon käynnistyksen funktio
    if (!running) { // Jos sekuntikello ei ole käynnissä
        running  = true; // Aseta kello käyntiin
        startTime = millis(); // Aseta aloitusaika
        lastPrintTime = millis(); // Aseta viimeisin tulostus
        Serial.println("Sekuntikello käynnistetty!");
    }
}

void stopTimer() { // Sekuntikellon pysäytyksen funktio
    if (running) { // Jos sekuntikello on käynnissä
        shouldStop = true; // Pysäytä kello
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(pinStart, INPUT_PULLUP); // Asetetaan pinnille 2 sisäinen ylösvetovastus // https://docs.arduino.cc/language-reference/en/variables/constants/inputOutputPullup/
    pinMode(pinStop, INPUT_PULLUP); // Asetetaan pinnille 3 sisäinen ylösvetovastus
    
    attachInterrupt(digitalPinToInterrupt(pinStart), startTimer, FALLING); // Keskeytys pinnille 2, kun painetaan maahan, eli FALLING // https://www.instructables.com/Arduino-Interrupts/
    attachInterrupt(digitalPinToInterrupt(pinStop), stopTimer, FALLING); // Keskeytys pinnille 3, kun se painetaan maahan, eli FALLING

    Serial.println("Paina pinniä 2 käynnistääksesi");
}

void loop() {
    if (running) { // Jos kello on käynnissä
        unsigned long currentTime = millis(); // Nykyinen aika
        unsigned long elapsed = currentTime - startTime; // Kulunut aika

        tenths = (elapsed / 100) % 10; // Lasketaan kymmenykset
        seconds = (elapsed / 1000) % 60; // Lasketaan sekunnit
        minutes = elapsed / 60000; // Lasketaan minuutit

        if (currentTime - lastPrintTime >= 1000) { // Jos on kulunut sekunti viimeisimmästä tulostuksesta
            Serial.print("Aika: ");
            Serial.print(minutes); // Tulostaa minuutit
            Serial.print(" min ");
            Serial.print(seconds); // Tulostaa sekunnit
            Serial.print(" s ");
            Serial.println();
            lastPrintTime = currentTime; // Päivittää tulostusajan
        }
        
        if (shouldStop) { // Jos sekuntikello pitäisi pysäyttää
            Serial.print("Lopetettu aika: ");
            Serial.print(minutes); // Tulostaa minuutit
            Serial.print(" min ");
            Serial.print(seconds); // Tulostaa sekunnit
            Serial.print(" s ");
            Serial.print(tenths); // Tulostaa kymmenykset
            Serial.println(" kymmenesosaa");

            running = false; // Pysäyttää sekuntikellon
            shouldStop = false; // Nollaa pysäytyksen
            tenths = 0; // Nollaa kymmenykset
            seconds = 0; // Nollaa sekunnit
            minutes = 0; // Nollaa minuutit

            Serial.println("Paina pinniä 2 käynnistääksesi uudelleen");
        }
    }
}