#include "CGameMenu.h"

CGameMenu::CGameMenu()
{
    nPosX = 400;
    nPosY = 200;
    nWidht = 414;  
    nHeight = 477;

    OldX = 0;
    OldY = 0;

    Surf_Interface = NULL;
    eInterfaceType = INTERFACE_GAMEMENU;
}

bool CGameMenu::OnLoad()
{
    if(CInterface::OnLoad() == false)
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
    CInterface::OnRender(Surf_Display);
}

void CGameMenu::OnCleanup()
{
    CInterface::OnCleanup();

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

void CGameMenu::UpdateButtonsPosition()
{
    if(OldX == 0 && OldY == 0)
        return;

    for(int i = 0;i < GameMenuButtonsList.size();i++) 
    {   
        if(!GameMenuButtonsList[i]) continue;
                
        GameMenuButtonsList[i]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
    }

    OldX = 0;
    OldY = 0;
}