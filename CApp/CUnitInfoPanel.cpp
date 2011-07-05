#include "CUnitInfoPanel.h"

CUnitInfoPanel::CUnitInfoPanel()
{
    nPosX = 5;
    nPosY = 5;
    nWidht = 600;
    nHeight = 30;

    eInterfaceType = INTERFACE_PLAYERINFO;

    Surf_Interface = NULL;
    Surf_UnitStatus = NULL;
}

bool CUnitInfoPanel::OnLoad()
{
    if(CInterface::OnLoad() == false) 
        return false;

    if((Surf_UnitStatus = CSurface::OnLoad("./interface/interface_unitinfo_status.png")) == NULL) 
        return false;

    return true;
}

void CUnitInfoPanel::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    if(CApp::pSelectedUnit != NULL) //If We Have Selected Player We Show Info
    {
        CSurface::OnDraw(Surf_Display, NULL /*CApp::pSelectedUnit->GetPortraitSurf()*/, nPosX + 26, nPosY + 39); // selected unit image

        //wez liczbe od gracza  i przekonwertuj na w

        CSurface::OnDraw(Surf_Display, Surf_UnitStatus, nPosX + 188, nPosY + 50, 0, 0, 200, 22); //hp

        CSurface::OnDraw(Surf_Display, Surf_UnitStatus, nPosX + 188, nPosY + 75, 0, 22, 251, 22); //mana

        //Show Name Lvl Etc.
    }
}

void CUnitInfoPanel::OnCleanup()
{
	CInterface::OnCleanup();

    if(Surf_UnitStatus) 
		SDL_FreeSurface(Surf_UnitStatus);

	Surf_UnitStatus = NULL;
}