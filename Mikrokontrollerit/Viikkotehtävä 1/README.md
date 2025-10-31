Tehtävä 1

Tehtävän korjattu koodi:

int printsubroutine(String s);
void setup()
{
  Serial.begin(2400);
}
void loop()
{
  if (Serial.available() > 0) // odotellaan, että vähintään yksi 8-bitin merkki on sarjamonitorilta tullut
    {
      int luettu = Serial.read();
      if (luettu == 49)
      {
        while (Serial.available() > 0)
        {
          Serial.read(); // luetaan ylimääräiset merkit pois
        }
        printSubroutine("Sinun pitaa saada tama teksti tulostumaan sarjamonitorille!");
      }
    }
}
void printSubroutine(String s)
{
  Serial.println(s);
}

Serial.read ja printSubroutine perästä puuttui ;
3. kohdan vastaus on 1, jotta saa tekstin tulostumaan.

Tehtävä 2
Tämän tehtävän koodi löytyy Tehtävä 2 kansiosta.

Tehtävä 3
Tämän tehtävän koodi löytyy Tehtävä 3 kansiosta.