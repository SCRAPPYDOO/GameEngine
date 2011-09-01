#ifndef _CINTERFACELOOT_H_
    #define _CINTERFACELOOT_H_

#include "CInterface.h"

class CInterfaceLoot : public CInterface
{
    public:
		CInterfaceLoot();
        ~CInterfaceLoot() {}

	public:	
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

		void OnButtonActivate(ButtonType Type);
		void LoadLoot(int UnitID) {}
};

#endif


