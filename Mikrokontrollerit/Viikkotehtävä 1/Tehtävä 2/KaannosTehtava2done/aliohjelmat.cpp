#include "aliohjelmat.h"  

int aliohjelma(int eka, int toka, char kolmas)
{
  // This subroutine should be able to do +, -, * and / operations
   /*int tulos = 0;
   tulos = eka + toka;
   return tulos; */

  int tulos = 0;  // lisätty toiminta laskurille
   switch (kolmas) {
     case '+': tulos = eka + toka; break;
     case '-': tulos = eka - toka; break;
     case '*': tulos = eka * toka; break;
     case '/':
       if (toka == 0) {
         tulos = 0;
       } else {
         tulos = eka / toka;
       }
       break;
     default:
       tulos = 0;
   }
   return tulos; 

   }
