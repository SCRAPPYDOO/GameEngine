#include "CInterface.h"
#include "CUnitInfoPanel.h"
#include "CButtonPanel.h"
#include "CGameMenu.h"
#include "CCharacterPanel.h"

CInterface CInterface::InterfaceControl;
std::vector<CInterface*> CInterface::InterfaceObjectList;

bool CInterface::IsGameMenu = false;

CInterface::CInterface() 
{
   CInterface::IsGameMenu = false;
}

bool CInterface::OnLoad()
{
    if((Surf_Interface = CSurface::OnLoad("./interface/surf_character_panel.png")) == NULL) 
        return false;

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

bool CInterface::OnLButtonUp(int x, int y)
{
    return false;
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

bool CInterface::LoadInterface()
{
    InterfaceObjectList.clear();

	if(LoadButtons() == false)
		return false;

    CUnitInfoPanel* pUnitInfoPanel = new CUnitInfoPanel();
    if(pUnitInfoPanel && pUnitInfoPanel->OnLoad() == false)
        return false;

    InterfaceObjectList.push_back(pUnitInfoPanel);

    CButtonPanel* pButtonPanel = new CButtonPanel();
    if(pButtonPanel && pButtonPanel->OnLoad() == false)
        return false;

    InterfaceObjectList.push_back(pButtonPanel);

    CCharacterPanel* pCharacterPanel = new CCharacterPanel();
    if(pCharacterPanel && pCharacterPanel->OnLoad() == false)
        return false;

    InterfaceObjectList.push_back(pCharacterPanel);

	return true;
}

bool CInterface::LoadSurface()
{
    if((Surf_Interface = CSurface::OnLoad("./menu/menu_background.png")) == NULL) 
	    return false;

	return true;
}

bool CInterface::LoadButtons()
{
    CButton::ButtonList.clear();

	ButtonType Type;

	switch(CApp::eGameState)
	{
		case MAIN_MENU:
		{
			for(int i=0; i<MAX_MENU_BUTTONS; ++i)
			{
				CButton *pButton = new CButton();

				switch(i)
				{
					case 0: Type = BUTTON_PLAY; break;
					case 1: Type = BUTTON_QUIT; break;
				}
					
				if(pButton->OnLoad(Type) == false)
                    return false;

				CButton::ButtonList.push_back(pButton);
			}

			break;
		}

        case TEST:
        {
            CButton *pButton = new CButton();
            pButton->OnLoad(BUTTON_MENU);
            CButton::ButtonList.push_back(pButton);

            break;
        }

        case GAME_MENU:
        {

            break;
        }

        default: break;
	}

	return true;
}

void CInterface::LoadInterface(InterfaceType eType)
{
    CInterface* pInterface = NULL;

    switch(eType)
    {
        case INTERFACE_GAMEMENU:
        {
            pInterface = new CGameMenu();
            if(pInterface && pInterface->OnLoad() == false)
                return;
        }

        default: break;
    }

    InterfaceObjectList.push_back(pInterface);
}

void CInterface::UnloadInterface(InterfaceType eType)
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

void CInterface::CleanUpInterface()
{
    for(int i = 0;i < InterfaceObjectList.size();i++) 
    {
        if(!InterfaceObjectList[i]) continue;

        InterfaceObjectList[i]->OnCleanup();
    }

    InterfaceObjectList.clear();
	CButton::ButtonList.clear();
}

bool CInterface::IsInterfaceOnPos(int nX, int nY)
{
    if( ( nX > nPosX ) && ( nX < nPosX + nWidht) && ( nY > nPosY ) && ( nY < nPosY + nHeight ) )
        return true;

    return false;
}
