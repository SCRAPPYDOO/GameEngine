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

    if(CArea::AreaControl.OnLoad("./maps/1.area") == false) 
    	return false;

    if(CInterface::InterfaceControl.OnLoad() == false)
        return false;

	CSurface::Surf_Colision = CSurface::OnLoad("colisioncircle.png");
	if(CSurface::Surf_Colision == NULL)
		return false;

    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if(Player.OnLoad("1.png", 64, 64, 8) == false) 
    {
        return false;
    }

    if(Player2.OnLoad("1.png", 64, 64, 8) == false)
    {
        return false;
    }

    CEntity::EntityList.push_back(&Player);
    CEntity::EntityList.push_back(&Player2);

    //CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    //CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    return true;
}

