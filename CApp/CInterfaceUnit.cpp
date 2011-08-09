#include "CInterfaceUnit.h"

CInterfaceUnit::CInterfaceUnit()
{
    nHealth             = 0;
    nMaxHealth          = 0;
    nHealthBarRange     = 0;
    Surf_UnitStatus     = NULL;
    Surf_UnitImage      = NULL;
    Surf_UnitName       = NULL;
    eInterfaceType = INTERFACE_PLAYERINFO;  
}

bool CInterfaceUnit::OnLoad()
{
    if(CInterface::OnLoad() == false) 
        return false;

    if((Surf_UnitStatus = CSurface::OnLoad("./interface/interface_unitinfo_status.png")) == NULL) 
        return false;

    if(CPlayer::Player.pPlayerCharacter != NULL)
    {
        char* name = CPlayer::Player.pPlayerCharacter->GetName();

        Surf_UnitName = RenderText(name);

        /*Surf_UnitImage = CPlayer::Player.pPlayerCharacter->GetImage();*/
    }

    return true;
}

void CInterfaceUnit::OnLoop()
{
    UpdateHealth();
}

void CInterfaceUnit::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    if(Surf_UnitImage)
        CSurface::OnDraw(Surf_Display, NULL /*CApp::pSelectedUnit->GetPortraitSurf()*/, nPosX + 26, nPosY + 39); // selected unit image

    if(Surf_UnitStatus)
        CSurface::OnDraw(Surf_Display, Surf_UnitStatus, nPosX, nPosY + INTERFACE_PLAYERINFO_H, 0, 0, nHealthBarRange, HEALTHBARHEIGHT); //hp

    if(Surf_UnitName)
        CSurface::OnDraw(Surf_Display, Surf_UnitName, nPosX, nPosY - 20);
}

void CInterfaceUnit::OnCleanup()
{
	CInterface::OnCleanup();

    if(Surf_UnitStatus) 
		SDL_FreeSurface(Surf_UnitStatus);

	Surf_UnitStatus = NULL;
}

void CInterfaceUnit::UpdateHealth()
{
    if(CPlayer::Player.pPlayerCharacter != NULL)
    {
        nHealth = CPlayer::Player.pPlayerCharacter->GetActualHealth();
        nMaxHealth = CPlayer::Player.pPlayerCharacter->GetMaxHealth();
    }

    nHealthBarRange = nHealth / (nMaxHealth / HEALTHBARRANGE);
}