#include <Arduino.h>

int lower, upper, rndmNumber, guess, guessAmount;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10000); // asettaa parseIntin timeoutin 10 sekunttiin, jottä käyttäjällä on aikaa syöttää

  // alustaa randomin generoinnin
  randomSeed(analogRead(0));

  start();
}

void tyhjenna_bufferi() {
  while (Serial.available() != 0) {
    char t = Serial.read();  // tyhjennetään bufferi aina parseIntin jälkeen
  }
}

void start() {
  guessAmount = 0;
  Serial.println("- Guessing game -");
  
  /* while (true) {
    Serial.println("lower: ");
    while (Serial.available() == 0) {}
    lower = (int)Serial.parseInt();
    tyhjenna_bufferi();

    Serial.println("upper: ");
    while (Serial.available() == 0) {}
    upper = (int)Serial.parseInt();
    tyhjenna_bufferi();

    if (lower >= upper) {
      Serial.println("Error, try again");
      continue;
    }
    break;
  } */

  Serial.println("lower: ");

  // Oottaa alarajaa
  while (Serial.available() == 0) {}
  lower = (int)Serial.parseInt();

  tyhjenna_bufferi();

  Serial.println("upper: ");

  // Oottaa ylärajaa
  while (Serial.available() == 0) {}
  upper = (int)Serial.parseInt();

  tyhjenna_bufferi();

  // Tarkistaa että arvaus on ylä ja alarajan sisällä
  if (lower >= upper) {
    Serial.println("error");  // Tämä ei toimi, mutta periaatteessa ei ole tarvetta.
    start();                  // Jos käyttäjä syöttää annettujen rajojen ulkopuolella olevan luvun, palauttaa ohjelma "liian iso" tai "liian pieni" vastauksen.
    return;
  }

  // Arvotaan luku syötteiden väliltä
  rndmNumber = random(lower, upper + 1);

  // Serial.print("DEBUG secret: "); // Nämä on debuggausta varten, tulostaa generoidun numeron
  // Serial.println(rndmNumber);

  Serial.println("Randomized number between ");
  Serial.println(lower);
  Serial.println(" - ");
  Serial.println(upper);
  Serial.println("Guess what number: ");
}

/*int get_random(int lowest, int highest) {
  int random_seed = analogRead(5);

  int modulo = random_seed % (highest - lowest); // Tämä oli debuggausta varten käytössä randomSeedin sijasta

  int result = lowest + modulo;

  return result;
} */

void loop() {

  tyhjenna_bufferi();

  // Tarkistaa käyttäjän arvauksen
  while (Serial.available() == 0) {}
    guess = Serial.parseInt();

    tyhjenna_bufferi();

    // Serial.println(guess); // Tämä on debuggausta varten, tulostaa arvatun numeron

    // Tarkistaa että syöte on numero
    if (guess != 0 || Serial.peek() == '0') {
      guessAmount++;

    // Tarkistaa arvauksen arvottuun lukuun
    if (guess < rndmNumber) {
      Serial.println("2 small, try again"); // Jos luku liian pieni, tulostaa tämän
    } else if (guess > rndmNumber) {
      Serial.println("2 big, try again"); // Jos luku liian suuri, tulostaa tämän
    } else {

      // Print tämä jos oikea vastaus
      Serial.println("Correct!");
      Serial.println("Your guess took ");
      Serial.println(guessAmount);
      Serial.println(" tries");

      // Aloittaa pelin uudelleen
      start();
    }
  }
}