#include "CInterfaceCharacterCreator.h"

CInterfaceCharacterCreator::CInterfaceCharacterCreator()
{
	OldX = 0;
    OldY = 0;
	eInterfaceType = INTERFACE_CHARACTERCREATOR;
}

bool CInterfaceCharacterCreator::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CInterfaceCharacterCreator::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);
}

void CInterfaceCharacterCreator::OnCleanup()
{
    CInterface::OnCleanup();
}