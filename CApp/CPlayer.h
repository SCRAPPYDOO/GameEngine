#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CUnit.h"

class CPlayer
{
    public:
        CPlayer()
        {
            pPlayerCharacter = NULL;
            pSelectedUnit = NULL;
            pTargetedUnit = NULL;
        }

        ~CPlayer() {}

    public:
        static CPlayer Player;
        CUnit* pPlayerCharacter;
        CUnit* pSelectedUnit;
        CUnit* pTargetedUnit;
};

#endif