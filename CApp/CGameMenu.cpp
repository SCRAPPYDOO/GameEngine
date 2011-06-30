#include "CGameMenu.h"

CGameMenu::CGameMenu()
{
    nPosX = 400;
    nPosX = 200;
    nWidht = 414;  
    nHeight = 477;
}

bool CGameMenu::OnLoad()
{
    if((Surf_GameMenu = CSurface::OnLoad("./menu/menu_gamebackground.png")) == NULL) 
        return false;

    return true;
}

void CGameMenu::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_GameMenu == NULL || Surf_Display == NULL) return;
    
    if(CInterface::InterfaceControl.ShowGameMenu == true)
        CSurface::OnDraw(Surf_Display, Surf_GameMenu, nPosX, nPosY);
}

void CGameMenu::OnCleanup()
{
	if(Surf_GameMenu) 
		SDL_FreeSurface(Surf_GameMenu);

    Surf_GameMenu = NULL;

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