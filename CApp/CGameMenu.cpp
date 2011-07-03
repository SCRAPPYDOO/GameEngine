#include "CGameMenu.h"

CGameMenu::CGameMenu()
{
    nPosX = 400;
    nPosY = 200;
    nWidht = 414;  
    nHeight = 477;
    eInterfaceType = INTERFACE_GAMEMENU;
}

bool CGameMenu::OnLoad()
{
    if((Surf_GameMenu = CSurface::OnLoad("./menu/menu_gamebackground.png")) == NULL) 
        return false;

    for(int i=10; i<12; ++i)
    {
        CButton *pButton = new CButton();

        ButtonType eType = BUTTON_DEFAULT;

        switch(i)
        {
            case 10: eType = BUTTON_GAMEMENU_QUIT; break;
            case 11: eType = BUTTON_GAMEMENU_RETURN; break;
        }

        if(pButton->OnLoad(eType) == false)
            return false;

        GameMenuButtonsList.push_back(pButton);
		CButton::ButtonList.push_back(pButton);
    }

    return true;
}

void CGameMenu::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_GameMenu == NULL || Surf_Display == NULL) return;
    
    CSurface::OnDraw(Surf_Display, Surf_GameMenu, nPosX, nPosY);
}

void CGameMenu::OnCleanup()
{
	if(Surf_GameMenu) 
		SDL_FreeSurface(Surf_GameMenu);

    Surf_GameMenu = NULL;

    for(int i = 0;i < GameMenuButtonsList.size();i++) 
    {   
        if(!GameMenuButtonsList[i]) continue;

        for(int n = 0;n < CButton::ButtonList.size();n++) 
        {   
            if(!CButton::ButtonList[n]) continue;

            if(CButton::ButtonList[n] == GameMenuButtonsList[i])
            {
                CButton::ButtonList[n]->OnCleanup();
                CButton::ButtonList[n] = NULL;  
            }
        }

        GameMenuButtonsList[i]->OnCleanup();
        GameMenuButtonsList[i] = NULL;
    }

    GameMenuButtonsList.clear();
}

void CGameMenu::OnMove(int nNextX, int nNextY)
{
    CInterface::OnMove(nNextX, nNextY);
    UpdateButtonsPosition();
}

void CGameMenu::UpdateButtonsPosition()
{
    for(int i = 0;i < GameMenuButtonsList.size();i++) 
    {   
        if(!GameMenuButtonsList[i]) continue;
                
        GameMenuButtonsList[i]->SetPositionX(nPosX + 30*i);
        GameMenuButtonsList[i]->SetPositionY(nPosY);
    }
}