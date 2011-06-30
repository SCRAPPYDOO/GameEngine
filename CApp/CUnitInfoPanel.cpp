#include "CUnitInfoPanel.h"

CUnitInfoPanel::CUnitInfoPanel()
{
    nPosX = 5;
    nPosY = 5;
    nWidht = 600;
    nHeight = 30;

    Surf_UnitInfoPanel = NULL;
    Surf_UnitStatus = NULL;
}

bool CUnitInfoPanel::OnLoad()
{
    if((Surf_UnitInfoPanel = CSurface::OnLoad("./interface/interface_unitinfo_surf.png")) == NULL) 
        return false;

    if((Surf_UnitStatus = CSurface::OnLoad("./interface/interface_unitinfo_status.png")) == NULL) 
        return false;

    return true;
}

void CUnitInfoPanel::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_UnitInfoPanel == NULL || Surf_UnitStatus == NULL || Surf_Display == NULL) return;
    
    CSurface::OnDraw(Surf_Display, Surf_UnitInfoPanel, nPosX, nPosY);

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
	if(Surf_UnitInfoPanel) 
		SDL_FreeSurface(Surf_UnitInfoPanel);

    if(Surf_UnitStatus) 
		SDL_FreeSurface(Surf_UnitStatus);

    Surf_UnitInfoPanel = NULL;
	Surf_UnitStatus = NULL;
}