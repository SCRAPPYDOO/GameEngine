#include "CInterface.h"
#include "CUnitInfoPanel.h"
#include "CButtonPanel.h"
#include "CGameMenu.h"

CInterface CInterface::InterfaceControl;
std::vector<CInterface*> CInterface::InterfaceObjectList;

CInterface::CInterface() 
{
    ShowGameMenu = false;
}

bool CInterface::OnLoad()
{
    if(LoadSurface() == false)
		return false;

	if(LoadButtons() == false)
		return false;

    return true;
}

void CInterface::OnRender(SDL_Surface* Surf_Display)
{
	if(Surf_BackGround == NULL || Surf_Display == NULL) return;

    switch(CApp::eGameState)
    {
        case MAIN_MENU:
        {
	        CSurface::OnDraw(Surf_Display, Surf_BackGround, 0, 0); //render BackGround
            break;
        }

        case TEST:
        {
            for(int i = 0;i < InterfaceObjectList.size();i++) 
            {   
                if(!InterfaceObjectList[i]) continue;
                
                InterfaceObjectList[i]->OnRender(Surf_Display);
            }

            break;
        }

        default: break;
    }

	for(int i = 0;i < CButton::ButtonList.size();i++) 
	{
            if(!CButton::ButtonList[i]) continue;

		    CButton::ButtonList[i]->OnRender(Surf_Display);	
	}
}

void CInterface::OnCleanup()
{
	if(Surf_BackGround) 
		SDL_FreeSurface(Surf_BackGround);

    if(Surf_MenuButton) 
		SDL_FreeSurface(Surf_MenuButton);

    Surf_MenuButton = NULL;
	Surf_BackGround = NULL;

    for(int i = 0;i < InterfaceObjectList.size();i++) 
    {
        if(!InterfaceObjectList[i]) continue;

        InterfaceObjectList[i]->OnCleanup();
    }

    InterfaceObjectList.clear();
	CButton::ButtonList.clear();
}

bool CInterface::OnLButtonUp(int x, int y)
{

 //   for(int i = 0;i < CButton::ButtonList.size();i++) 
	//{
 //       if(!CButton::ButtonList[i]) continue;

	//	if( ( x > CButton::ButtonList[i]->GetPosX() ) && ( x < CButton::ButtonList[i]->GetPosX() + CButton::ButtonList[i]->GetWidht()) && ( y > CButton::ButtonList[i]->GetPosY() ) && ( y < CButton::ButtonList[i]->GetPosY() + CButton::ButtonList[i]->GetHeight() ) )
 //       {
 //           CButton::ButtonList[i]->Activate();
 //           return true;
 //       }
 //   }

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

    CGameMenu* pGameMenu = new CGameMenu();
    if(pGameMenu && pGameMenu->OnLoad() == false)
        return false;

    InterfaceObjectList.push_back(pGameMenu);

	return true;
}

bool CInterface::LoadSurface()
{
    if((Surf_BackGround = CSurface::OnLoad("./menu/menu_background.png")) == NULL) 
	    return false;

	if((Surf_MenuButton = CSurface::OnLoad("./menu/menu_buttons.png")) == NULL) 
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
				CButton *Button = new CButton();

				switch(i)
				{
					case 0: Type = BUTTON_PLAY; break;
					case 1: Type = BUTTON_QUIT; break;
				}
					
				if(Button->OnLoad(Type) == false)
                    return false;

				CButton::ButtonList.push_back(Button);
			}

			break;
		}

        case TEST:
        {

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

