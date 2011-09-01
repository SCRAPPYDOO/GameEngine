#include "CInterfaceLoot.h"

CInterfaceLoot::CInterfaceLoot()
{
	OldX = 0;
    OldY = 0;
	eInterfaceType = INTERFACE_LOOT;
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