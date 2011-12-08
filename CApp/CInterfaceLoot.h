#ifndef _CINTERFACELOOT_H_
    #define _CINTERFACELOOT_H_

#include "CInterface.h"

struct Loot
{
	int nGuid;   //Guid of unit
	std::vector <int> UnitLootList;
};

class CInterfaceLoot : public CInterface
{
    public:
		CInterfaceLoot();
		CInterfaceLoot(int nGuid, int nID);
        ~CInterfaceLoot() {}

	public:	
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

		void OnButtonActivate(ButtonType Type);
		void LoadLoot(int nGuid, int nID);

	private:
		std::vector <int> LootBoxList;
		std::vector <Loot> LootListHandler;
};

#endif


