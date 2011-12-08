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

    CSurface::Font = TTF_OpenFont( "./font/times.ttf", 15 );
    if(CSurface::Font == NULL) return false;

    if(CInterfaceMenager::InterfaceMenager.LoadInterface() == false)
        return false;

	//DEBUG 
	//Created terst units

    //Test Character don delete this for now
	CUnit* unit = new CCharacter();
	unit->OnLoad();
	CUnitMenager::UnitList.push_back(unit);
	CPlayer::Player.pPlayerCharacter = unit;

    //Test Character don delete this for now
	CUnit* punit = new CCharacter();
	punit->OnLoad();
	CUnitMenager::UnitList.push_back(punit);
    return true;
}

