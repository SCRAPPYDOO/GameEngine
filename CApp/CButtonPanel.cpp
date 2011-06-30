#include "CButtonPanel.h"

CButtonPanel::CButtonPanel()
{
    nPosX = 300;
    nPosY = 600;
    nWidht = 600;
    nHeight = 30;

    Surf_ButtonPanel = NULL;
}

bool CButtonPanel::OnLoad()
{
    if((Surf_ButtonPanel = CSurface::OnLoad("./interface/interface_button_surf.png")) == NULL) 
        return false;

    AddButton();

    //Load cfg

    return true;
}

void CButtonPanel::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_ButtonPanel == NULL || Surf_Display == NULL) return;
    
    CSurface::OnDraw(Surf_Display, Surf_ButtonPanel, nPosX, nPosY);
}

void CButtonPanel::OnCleanup()
{
	if(Surf_ButtonPanel) 
		SDL_FreeSurface(Surf_ButtonPanel);

    Surf_ButtonPanel = NULL;

    PanelButtonsPlace.clear();
}

void CButtonPanel::OnMove(int nNextX, int nNextY)
{
    CInterface::OnMove(nNextX, nNextY);
    UpdateButtonsPosition();
}

void CButtonPanel::UpdateButtonsPosition()
{
    for(int i = 0;i < PanelButtonsPlace.size();i++) 
    {   
        if(!PanelButtonsPlace[i]) continue;
                
        PanelButtonsPlace[i]->SetPositionX(nPosX + 30*i);
        PanelButtonsPlace[i]->SetPositionY(nPosY);
    }
}



//TEST
void CButtonPanel::AddButton()
{
    CButton* pButton = new CButton(nPosX, nPosY, BUTTON_QUIT, CInterface::InterfaceControl.Surf_MenuButton);

    if(pButton != NULL)
    {
        PanelButtonsPlace.push_back(pButton);
        CButton::ButtonList.push_back(pButton);
    }
}

//On LButtonUp(int nX, int nY