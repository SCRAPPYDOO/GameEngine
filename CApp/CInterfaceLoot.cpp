#include "CInterfaceLoot.h"

CInterfaceLoot::CInterfaceLoot()
{
	OldX = 0;
    OldY = 0;
	eInterfaceType = INTERFACE_LOOT;
}

CInterfaceLoot::CInterfaceLoot(int nGuid, int nID)
{


}

bool CInterfaceLoot::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

	return true;
}

void CInterfaceLoot::OnLoop()
{
    CInterface::OnLoop();
}

void CInterfaceLoot::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);
}

void CInterfaceLoot::OnCleanup()
{
    CInterface::OnCleanup();
}

void CInterfaceLoot::OnButtonActivate(ButtonType Type)
{
    switch(Type)
    {
        default: break;
    }
}

void CInterfaceLoot::LoadLoot(int nGuid, int nID)
{
	//sporawdz w  liscie lootu po nGUID czy jest juz yegenerowany jezlei tak otwoerz
	for(int i=0; i<LootListHandler.size(); ++i)
	{
		if(!LootListHandler[i].nGuid) continue;

		//jezeli mamy juz wygenerowany loot dla danego guida ladujemy go
		if(LootListHandler[i].nGuid == nGuid)
		{
			for(int n=0; n<LootListHandler[i].UnitLootList.size(); ++n)
			{
				if(!LootListHandler[i].UnitLootList[n]) continue;

				LootBoxList.push_back(LootListHandler[i].UnitLootList[n]);
			}
			//load loot 
			return;
		}
	}
	
	//jezlei nie  wylosuj loot po ID

}
