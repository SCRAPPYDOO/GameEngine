#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

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

        static CPlayer Player;

    public:
        
        CUnit* pPlayerCharacter;
        CUnit* pSelectedUnit;
        CUnit* pTargetedUnit;
		int nSelectedSpell;

		void LoadCharacter(int CharID) 
		{
			//zaladuj wszytko z plikuj lub z bazy
			//pPlayerCharacter = new CCharacter();
			//pPlayerCharacter->LoadCharFromFile(CharID);
			//dodaj do listy unitow
		}
};

#endif