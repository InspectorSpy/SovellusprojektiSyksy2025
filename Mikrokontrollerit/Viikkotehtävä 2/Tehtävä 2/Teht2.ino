/*
Tee aliohjelma, jonka prototyyppi (=määrittely) on muotoa float analogCompare(int), joka ottaa inputtina analogiapinnin numeron 1,..,5.
Ohjelma mittaa analogia jännitteen asteikolla 0-5 volttia referenssipinnistä A0 ja käyttäjän antamasta analogia pinnistä (1-5) ja palauttaa jännitteiden eron.
Testaa ohjelmasi toiminta syöttämällä hyppylangalla 5V A0-pinniin ja 3.3V aliohjelmalle määriteltyyn pinniin.
Käytä aliohjelmasi toteutuksessa switch-case rakennetta (jotta muistuisi mieleen tuokin rakenne)
*/

#include <Arduino.h>

float analogCompare(int analogPin) {
    int arduinoPin;
    switch (analogPin) {
        case 1: arduinoPin = A1; break; // Pinni A1 käytössä mittauksissa
        case 2: arduinoPin = A2; break; // Loput pinnit on määritelty, mutta ei käytössä
        case 3: arduinoPin = A3; break; // Niitä kyllä voi käyttää
        case 4: arduinoPin = A4; break;
        case 5: arduinoPin = A5; break;
        default: return 0.0; // Jos pinni on väärä, palauttaa monitoriin 0.0
    }

    int refValue = analogRead(A0);         // Referenssijännite pinnistä A0
    int pinValue = analogRead(arduinoPin); // Jännite valitusta pinnistä

    float refVoltage = refValue * (5.0 / 1023.0); // Muunnetaan ADC-arvot volteiksi (0-1023 -> 0-5V)
    float pinVoltage = pinValue * (5.0 / 1023.0);

    return refVoltage - pinVoltage; // Palautetaan jännitteiden erotus
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    int analogPin = 1; // Käytetään mittauksessa AnalogIn pinniä nro 1
    float voltageDifference = analogCompare(analogPin); // Kutsuu analogCompare aliohjelmaa 
    Serial.print("Voltage difference: "); // Tulostaa jännitteiden eron monitoriin
    Serial.println(voltageDifference);
    delay(1000); // Odottaa 1 sekunnnin ennen seuraavaa mittausta
}