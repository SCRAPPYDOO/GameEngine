#include "CInterfaceUnit.h"

CInterfaceUnit::CInterfaceUnit()
{
    pUnit               = NULL; 
    nHealth             = 0;
    nMaxHealth          = 0;
    nHealthBarRange     = 0;
    Surf_UnitStatus     = NULL;
    Surf_UnitImage      = NULL;
    Surf_UnitName       = NULL;
    Surf_Percentage     = NULL; 
    eInterfaceType      = INTERFACE_PLAYERINFO;
}

CInterfaceUnit::CInterfaceUnit(InterfaceType eType)
{
    pUnit               = NULL;      
    nHealth             = 0;
    nMaxHealth          = 0;
    nHealthBarRange     = 0;
    Surf_UnitStatus     = NULL;
    Surf_UnitImage      = NULL;
    Surf_UnitName       = NULL;
    Surf_Percentage     = NULL; 
    eInterfaceType = eType;
}

bool CInterfaceUnit::OnLoad()
{
    if(CInterface::OnLoad() == false) 
        return false;

    if((Surf_UnitStatus = CSurface::OnLoad("./interface/interface_unitinfo_status.png")) == NULL) 
        return false;

    UpdateUnit();

    if(pUnit)
    {
        char* name = pUnit->GetName();
        if(name)
            Surf_UnitName = RenderText(name);

        /*Surf_UnitImage = CPlayer::Player.pPlayerCharacter->GetImage();*/
    }

    return true;
}

void CInterfaceUnit::OnLoop()
{
    CInterface::OnLoop();

    UpdateUnit();
    UpdateHealth();
}

void CInterfaceUnit::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    if(Surf_UnitImage)
        CSurface::OnDraw(Surf_Display, NULL /*CApp::pSelectedUnit->GetPortraitSurf()*/, nPosX + 26, nPosY + 39); // selected unit image

    if(Surf_UnitStatus)
        CSurface::OnDraw(Surf_Display, Surf_UnitStatus, nPosX, nPosY + INTERFACE_PLAYERINFO_H, 0, 0, nHealthBarRange, HEALTHBARHEIGHT); //hp

    if(Surf_Percentage)
        CSurface::OnDraw(Surf_Display, Surf_Percentage, nPosX + 0.5 * INTERFACE_PLAYERINFO_H, nPosY + INTERFACE_PLAYERINFO_H); //hp

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
    if(pUnit)
    {
        nHealth = pUnit->GetActualHealth();
        nMaxHealth = pUnit->GetMaxHealth();
        nHealthBarRange = nHealth / (nMaxHealth / HEALTHBARRANGE);
    }

    std::string s = ConvertIntToString(nHealthBarRange) + "%";

    Surf_Percentage = RenderText(s);
}

void CInterfaceUnit::UpdateUnit()
{
    switch(eInterfaceType)
    {
        case INTERFACE_PLAYERINFO:
        {
            if(CPlayer::Player.pPlayerCharacter != NULL)
                pUnit = CPlayer::Player.pPlayerCharacter;
            break;
        }

        case INTERFACE_TARGET:
        {
            if(CPlayer::Player.pTargetedUnit != NULL)
                pUnit = CPlayer::Player.pTargetedUnit;
            break;
        }

        default: pUnit = NULL; break;
    }
}