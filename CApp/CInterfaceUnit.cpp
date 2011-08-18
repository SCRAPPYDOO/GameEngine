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
        std::string name = pUnit->GetName();

        Surf_UnitName = CSurface::RenderText(name);

        /*Surf_UnitImage = CPlayer::Player.pPlayerCharacter->GetImage();*/
    }

    return true;
}

void CInterfaceUnit::OnLoop()
{
    CInterface::OnLoop();
    CleanUpHealthBar();
    UpdateUnit();
    UpdateHealth();
}

void CInterfaceUnit::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Display == NULL) return;

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

    if(Surf_UnitImage)
        SDL_FreeSurface(Surf_UnitImage);

    if(Surf_UnitName)
        SDL_FreeSurface(Surf_UnitName);

    if(Surf_UnitStatus)
        SDL_FreeSurface(Surf_UnitStatus);

    Surf_UnitStatus = NULL;
    Surf_UnitName = NULL;
    Surf_UnitImage = NULL;

    CleanUpHealthBar();
}

void CInterfaceUnit::CleanUpHealthBar()
{
    if(Surf_Percentage)
        SDL_FreeSurface(Surf_Percentage);

    Surf_Percentage = NULL;
}

void CInterfaceUnit::UpdateHealth()
{
    if(!pUnit) return;

    nHealth = pUnit->GetActualHealth();
    nMaxHealth = pUnit->GetMaxHealth();
    nHealthBarRange = nHealth / (nMaxHealth / HEALTHBARRANGE);  

    Surf_Percentage = CSurface::RenderText(nHealthBarRange);
}

void CInterfaceUnit::UpdateUnit()
{
    switch(eInterfaceType)
    {
        case INTERFACE_PLAYERINFO:
        {
            if(CPlayer::Player.pPlayerCharacter != NULL)
                pUnit = CPlayer::Player.pPlayerCharacter;
            else pUnit = NULL;

            break;
        }

        case INTERFACE_TARGET:
        {
            if(CPlayer::Player.pTargetedUnit != NULL)
                pUnit = CPlayer::Player.pTargetedUnit;
            else pUnit = NULL;

            break;
        }

        default: pUnit = NULL; break;
    }
}
