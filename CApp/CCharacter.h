#ifndef _CCHARACTER_H_
    #define _CCHARACTER_H_

#include "CUnit.h"



class CCharacter : public CUnit
{
    public:
        CCharacter();
        ~CCharacter() {}

    public:


    protected:
        char* cCharacterName;

        int nActualHealth;
        int nMaxHealth;

    public:
        //Character Methods
        char* GetName() { return cCharacterName; }
        int GetActualHealth() const { return nActualHealth; }
        int GetMaxHealth() const { return nMaxHealth; }

};

#endif