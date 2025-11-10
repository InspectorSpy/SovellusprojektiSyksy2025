/*
1: Tee sekuntikello käyttäen Loop-rakennetta ja Timeria. Sekuntikellon tulee laskea sekunnin kymmenyksiä, sekunteja ja minuutteja

- Sekuntikello käynnistetään maadoittamalla pinni 2 (voit käyttää keskeytyksiä apuna)

- Sekuntikello päivittää ajan sarjaportille sekunnin välein.

- Sekuntikello pysäytetään maadoittamalla pinni 3, jolloin tulostetaan tarkka aika kymmenyksineen, ja nollataan aika uutta ajanottoa varten.
*/

#include <Arduino.h>

uint8_t pinStart = 2;
uint8_t pinStop = 3;

volatile bool running = false;
volatile bool shouldStop = false;

unsigned long startTime = 0;
unsigned long lastPrintTime = 0;

unsigned int tenths = 0;
unsigned int seconds = 0;
unsigned int minutes = 0;

void startTimer() {
    if (!running) {
        running  = true;
        startTime = true;
        lastPrintTime = millis();
        Serial.println("Sekuntikello käynnistetty!");
    }
}

void stopTimer() {
    if (running) {
        shouldStop = true;
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(pinStart, INPUT_PULLUP);
    pinMode(pinStop, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(pinStart), startTimer, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinStop), stopTimer, FALLING);

    Serial.println("Paina pinniä 2 käynnistääksesi");
}

void loop() {
    if (running) {
        unsigned long currentTime = millis();
        unsigned long elapsed = currentTime - startTime;

        tenths = (elapsed / 100) % 10;
        seconds = (elapsed / 1000) % 60;
        minutes = elapsed / 60000;

        if (currentTime - lastPrintTime >= 1000) {
            Serial.print("Aika: ");
            Serial.print(minutes);
            Serial.print(" min ");
            Serial.print(seconds);
            Serial.print(" s ");
            Serial.println();
            lastPrintTime = currentTime;
        }
        
        if (shouldStop) {
            Serial.print("Lopetettu aika: ");
            Serial.print(minutes);
            Serial.print(" min ");
            Serial.print(seconds);
            Serial.print(" s ");
            Serial.print(tenths);
            Serial.println(" kymmenesosaa");

            running = false;
            shouldStop = false;
            tenths = 0;
            seconds = 0;
            minutes = 0;

            Serial.println("Paina pinniä 2 käynnistääksesi uudelleen");
            delay(500);
        }
    }
}