#ifndef _CDICE_H_
    #define _CDICE_H_


#include <cstdlib>
#include <iostream>
#include <ctime>
#include <conio.h>

enum DICE_TYPE 
{ 
     D4 = 4, 
     D6 = 6, 
     D8 = 8, 
     D10 = 10, 
     D12 = 12, 
     D20 = 20, 
     D100 = 100, 
};

static int RollDice(int nNumbOfDice, DICE_TYPE nDiceType)
{
     srand (static_cast<unsigned int>(time(NULL)));
     int nRoll = 0;
     int nP;
     for(int i=0; i<nNumbOfDice; ++i)
     {
         nP = rand()%static_cast<int>(nDiceType)+1; 
         std::cout << nP; " " ;
         nRoll = nRoll+nP;
     };
     return nRoll;
};

#endif