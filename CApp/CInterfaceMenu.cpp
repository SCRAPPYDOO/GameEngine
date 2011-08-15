#include "CInterfaceMenu.h"

CInterfaceMenu::CInterfaceMenu()
{
	OldX = 0;
    OldY = 0;
	Surf_character = NULL;
	eInterfaceType = INTERFACE_MAINMENU;
}

bool CInterfaceMenu::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

	LoadCharacters();

    return true;
}

void CInterfaceMenu::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);

	if(Surf_character == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_character, 6, 6);
}

void CInterfaceMenu::OnCleanup()
{
    CInterface::OnCleanup();

	if(Surf_character) 
		SDL_FreeSurface(Surf_character);

	Surf_character = NULL;
}

bool CInterfaceMenu::LoadCharacters()
{

	//load characters from db

	if((Surf_character = CSurface::OnLoad("./interface/interface_unitinfo_portreit.png")) == NULL) 
		return false;

	return true;
}