#include "CApp.h"

bool CApp::OnInit() 
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) 
    {
        return false;
    }

 /*   if(CArea::AreaControl.OnLoad("./maps/1.area") == false) 
    	return false;*/

    if(CInterface::InterfaceControl.LoadInterface() == false)
        return false;

	/*
	CSurface::Surf_Colision = CSurface::OnLoad("./test/colisioncircle.png");  //test colision circle
	if(CSurface::Surf_Colision == NULL)
		return false;
		*/

	/*
    if(Player.OnLoad("./anim/1.png", 64, 64, 8) == false) 
    {
        return false;
    }

    if(Player2.OnLoad("./anim/1.png", 64, 64, 8) == false)
    {
        return false;
    }

    CEntity::EntityList.push_back(&Player);
    CEntity::EntityList.push_back(&Player2);
	*/

    return true;
}

