#include "CInterface.h"
#include "CUnitInfoPanel.h"
#include "CButtonPanel.h"
#include "CInterfaceA.h"
#include "CInterfaceBag.h"
#include "CInterfaceLoot.h"

CInterface CInterface::InterfaceControl;

CInterface::CInterface() 
{
    nInterfaceFlag = 0;

	for(int i=0; i<MAX_INTERFACEOBJECTS; ++i)
	{
		Interface[i] = NULL;
	}
}

bool CInterface::OnLoad()
{
    char* SurfName = "./error/surf_error.png";

    //ToDo: Load cfg from file
    switch(eInterfaceType)
    {
        case INTERFACE_MAINMENU:
        {
            nWidht = INTERFACE_MAINMENU_W;
            nHeight = INTERFACE_MAINMENU_H;
            SurfName = "./menu/main_menu_surf.png"; break;
        }
        case INTERFACE_PLAYERINFO: SurfName = "./interface/interface_unitinfo_surf.png"; break;
        case INTERFACE_BUTTON_PANEL: SurfName = "./interface/interface_button_surf.png"; break;
        case INTERFACE_GAMEMENU: 
        {
            nWidht = INTERFACE_GAMEMENU_W;
            nHeight = INTERFACE_GAMEMENU_H;
            SurfName = "./menu/menu_gamebackground.png"; break;
        }
        case INTERFACE_CHARACTERPANEL: 
        {
            nWidht = INTERFACE_CHARACTERPANEL_W;
            nHeight = INTERFACE_CHARACTERPANEL_H; 
            SurfName = "./interface/surf_character_panel.png"; break;
        }
        case INTERFACE_BAG: SurfName = "./interface/interface_equpment_surf.png"; break;
        case INTERFACE_LOOT: SurfName = "./interface/interface_loot_surf.png"; break;
        default: break;
    }

    if((Surf_Interface = CSurface::OnLoad(SurfName)) == NULL) 
        return false;

    LoadButtons();

    return true;
}

void CInterface::OnLoop()
{
    UpdateButtonsPosition();
}

void CInterface::OnRender(SDL_Surface* Surf_Display)
{
	if(Surf_Interface == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Interface, nPosX, nPosY);
}

void CInterface::OnCleanup()
{
	if(Surf_Interface) 
		SDL_FreeSurface(Surf_Interface);

	Surf_Interface = NULL;
}

bool CInterface::LoadInterface()
{
    CleanUpInterface();

    switch(CApp::eGameState)
    {
        case MAIN_MENU:
        {
            if(LoadInterface(INTERFACE_MAINMENU) == false)
                return false;

            break;
        }

        case TEST:
        {
            InterfaceType eType;

            for(int i=0; i<4; ++i)
            {
                switch(i)
                {
                    case 0: eType = INTERFACE_PLAYERINFO; break;      
                    case 1: eType = INTERFACE_BUTTON_PANEL; break;           
                    case 2: eType = INTERFACE_CHARACTERPANEL; break;
                    case 3: eType = INTERFACE_LOOT          ; break;
                    default: break;
                }

                if(LoadInterface(eType) == false)
                    return false;
            }

            break;
        }

        default: return false;
    }

	return true;
}

bool CInterface::LoadInterface(InterfaceType eType)
{
    CInterface* pInterface = NULL;

    switch(eType)
    {
        case INTERFACE_MAINMENU: pInterface = new CInterfaceA(eType); break;
        case INTERFACE_PLAYERINFO: pInterface = new CUnitInfoPanel(); break;
        case INTERFACE_BUTTON_PANEL: pInterface = new CButtonPanel(); break;
        case INTERFACE_GAMEMENU: pInterface = new CInterfaceA(eType); break;
        case INTERFACE_CHARACTERPANEL: pInterface = new CInterfaceA(eType); break;
        case INTERFACE_BAG: pInterface = new CInterfaceBag(); break;
        case INTERFACE_LOOT: pInterface = new CInterfaceLoot(); break;
        default: return false;
    }

    if(pInterface && pInterface->OnLoad() == false)
        return false;

	Interface[eType] = pInterface;

    return true;
}

CInterface* CInterface::GetInterface(int nPosX, int nPosY)
{
	for(int i = 0; i < MAX_INTERFACEOBJECTS; i++) 
    {   
        if(!Interface[i]) continue;
                
        if( ( nPosX > Interface[i]->GetPosX() ) && ( nPosX < Interface[i]->GetPosX() + Interface[i]->GetWidht()) && ( nPosY > Interface[i]->GetPosY() ) && ( nPosY < Interface[i]->GetPosY() + Interface[i]->GetHeight() ) )
        {
            return Interface[i];
        }
    }

    return NULL;
}

void CInterface::CleanUpInterface()
{
	for(int i = 0;i < MAX_INTERFACEOBJECTS;i++) 
    {
        if(!Interface[i]) continue;

        Interface[i]->OnCleanup();
		Interface[i] = NULL;
    }
}

void CInterface::CleanUpInterface(InterfaceType eType)
{	
	if(Interface[eType] == NULL)
		return;

	Interface[eType]->OnCleanup();
	Interface[eType] = NULL; 
}

bool CInterface::IsInterfaceOnPos(int nX, int nY)
{
    if( ( nX > nPosX ) && ( nX < nPosX + nWidht) && ( nY > nPosY ) && ( nY < nPosY + nHeight ) )
        return true;

    return false;
}

void CInterface::OnMove(int nNextX, int nNextY) 
{ 
    OldX = nPosX;
    OldY = nPosY;

    nPosX = nNextX - nDistX; 
    nPosY = nNextY - nDistY;   
}   
