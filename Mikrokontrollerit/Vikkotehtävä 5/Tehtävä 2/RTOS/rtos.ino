/*
Asenna FreeRTOS kirjasto

Tee ohjelma (hyödynnä esimerkkiä), jossa on kaksi taskia:

ensimmäinen lukee numeroita sarjaportista jatkuvasti ja lisää ne muuttujaan

toinen vähentää muuttujan arvoa sekunnin välein ja tulostaa lukeman sarjaporttiin, jos lukema on yli 0.
*/

#include <Arduino.h>
#include <FreeRTOS.h>

volatile long int laskin = 0; // muuttuja, käytössä molemmissa taskeissa

void TaskLueSarjaportti(void *pvParameters); // Eka task
void TaskVahennaLukema(void *pvParameters); // Toka task

void setup() {
    Serial.begin(9600);

    Serial.println("Aloita");

    while (!Serial) {
        ; // odota portin kytkeytymistä
    }
}

xTaskCreate(TaskLueSarjaportti, "LueSarjaportti", 128, NULL, 1, NULL); // Eka task
xTaskCreate(TaskVahennaLukema, "Vahennalukema", 128, NULL, 2, NULL); // Toka task

void loop() {
    // ei tarvetta loopille, miksi? Ilmeisesti koska FreeRTOS hoitaa taskit
}

void TaskLueSarjaportti(void *pvParameters) { // Eka task
    (void) pvParameters; // Estä varoitus käyttämättömästä parametrista

    while (1) { // Infinite loop
        laskin += Serial.parseInt(); // Lue sarjaportista ja lisää luku laskuriin
    }
}

void TaskVahennaLukema(void *pvParameters) { // Toka task
    (void) pvParameters; // Estä varoitus käyttämättömästä parametrista

    while (1) { // Infinite loop
        if (laskin > 0) { // Jos laskuri on > 0, vähennä ja tulosta
            Serial.println(laskin); // Tulosta sarjaporttiin
        }
        laskin--; // Vähennä laskuria
        vTaskDelay(pdMS_TO_TICKS(1000)); // Odota 1 sekunti, parempi kuin delay. Thanks Miiro xd
    }
}