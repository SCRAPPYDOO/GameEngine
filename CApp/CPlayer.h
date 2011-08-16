#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CUnit.h"
#include "CCharacter.h"

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

		bool OnLoad() 
		{
			return true;
		}

    public:
        static CPlayer Player;
        CUnit* pPlayerCharacter;
        CUnit* pSelectedUnit;
        CUnit* pTargetedUnit;

	public:

};

#endif