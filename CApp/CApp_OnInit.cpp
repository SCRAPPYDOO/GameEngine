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

    if( TTF_Init() == -1 )
    {
        return false;
    }

	if(CPlayer::Player.OnLoad() == false)
		return false;

    if(CInterfaceMenager::InterfaceMenager.LoadInterface() == false)
        return false;

    return true;
}

