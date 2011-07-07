#include "CInterface.h"
#include "CUnitInfoPanel.h"
#include "CButtonPanel.h"
#include "CInterfaceA.h"
#include "CInterfaceB.h"

CInterface CInterface::InterfaceControl;
std::vector<CInterface*> CInterface::InterfaceObjectList;

bool CInterface::IsGameMenu = false;

CInterface::CInterface() 
{
    CInterface::IsGameMenu = false;
}

bool CInterface::OnLoad()
{
    char* SurfName = "./error/surf_error.png";

    //ToDo: Load cfg from file
    switch(eInterfaceType)
    {
        case INTERFACE_MAINMENU: 
        {
            CInterface::IsGameMenu = false;
            SurfName = "./menu/main_menu_surf.png"; 
            break;
        }
        case INTERFACE_PLAYERINFO: SurfName = "./interface/interface_unitinfo_surf.png"; break;
        case INTERFACE_BUTTON_PANEL: SurfName = "./interface/interface_button_surf.png"; break;
        case INTERFACE_GAMEMENU: SurfName = "./menu/menu_gamebackground.png"; break;
        case INTERFACE_CHARACTERPANEL: SurfName = "./interface/surf_character_panel.png"; break;
        case INTERFACE_BAG:
        {
            SurfName = "./interface/interface_equpment_surf.png"; break;
        }

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
    DeleteMovedButtons();
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

            for(int i=0; i<MAX_INTERFACEOBJECTS; ++i)
            {
                switch(i)
                {
                    case 0: eType = INTERFACE_PLAYERINFO; break;      
                    case 1: eType = INTERFACE_BUTTON_PANEL; break;           
                    case 2: eType = INTERFACE_CHARACTERPANEL; break;
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
        case INTERFACE_BAG: pInterface = new CInterfaceB(eType); break;

        default: return false;
    }

    if(pInterface && pInterface->OnLoad() == false)
        return false;

    InterfaceObjectList.push_back(pInterface);
    return true;
}

CInterface* CInterface::GetInterface(int nPosX, int nPosY)
{
    CInterface* pInterface = NULL;

    for(int i = 0;i < InterfaceObjectList.size();i++) 
    {   
        if(!InterfaceObjectList[i]) continue;
                
        if( ( nPosX > InterfaceObjectList[i]->GetPosX() ) && ( nPosX < InterfaceObjectList[i]->GetPosX() + InterfaceObjectList[i]->GetWidht()) && ( nPosY > InterfaceObjectList[i]->GetPosY() ) && ( nPosY < InterfaceObjectList[i]->GetPosY() + InterfaceObjectList[i]->GetHeight() ) )
        {
            pInterface = InterfaceObjectList[i];
            break;
        }
    }

    return pInterface;
}

void CInterface::CleanUpInterface()
{
    for(int i = 0;i < InterfaceObjectList.size();i++) 
    {
        if(!InterfaceObjectList[i]) continue;

        InterfaceObjectList[i]->OnCleanup();
    }

    InterfaceObjectList.clear();
}

void CInterface::CleanUpInterface(InterfaceType eType)
{
    for(int n = 0;n < InterfaceObjectList.size();n++) 
    {   
        if(!InterfaceObjectList[n]) continue;

        if(InterfaceObjectList[n]->GetInterfaceType() == eType)
        {
            InterfaceObjectList[n]->OnCleanup();
            InterfaceObjectList[n] = NULL; 
            return;
        }
    }
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