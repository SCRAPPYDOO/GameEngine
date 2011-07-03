#include "CButtonPanel.h"

CButtonPanel::CButtonPanel()
{
    nPosX               = 300;
    nPosY               = 600;
    nWidht              = 600;
    nHeight             = 60;

    Surf_ButtonPanel    = NULL;
    eInterfaceType      = INTERFACE_BUTTON_PANEL;

    for(int i=0; i<MAX_BUTTON_SLOTS; ++i)
    {
        ButtonSlot[i] = NULL;
    }
}

bool CButtonPanel::OnLoad()
{
    if((Surf_ButtonPanel = CSurface::OnLoad("./interface/interface_button_surf.png")) == NULL) 
        return false;

    AddButton();

    //Load cfg

    return true;
}

void CButtonPanel::OnLoop()
{
    DeleteMovedButtons();
    UpdateButtonsPosition();
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

    for(int i=0;i < MAX_BUTTON_SLOTS; ++i)
    {
        ButtonSlot[i] = NULL;
    }
}

void CButtonPanel::OnMove(int nNextX, int nNextY)
{
    CInterface::OnMove(nNextX, nNextY);
}

void CButtonPanel::UpdateButtonsPosition()
{
    for(int i = 0;i < MAX_BUTTON_SLOTS;i++) 
    {   
        if(!ButtonSlot[i]) continue;
                
        ButtonSlot[i]->SetPositionX(nPosX + 33*i +3);
        ButtonSlot[i]->SetPositionY(nPosY + 3);
    }
}

//TEST
void CButtonPanel::AddButton()
{
    CButton* pButton = new CButton(nPosX+3, nPosY+3, BUTTON_QUIT, CInterface::InterfaceControl.Surf_MenuButton);

    if(pButton != NULL)
    {
        ButtonSlot[0] = pButton;
        CButton::ButtonList.push_back(pButton);
    }

    CButton* pButton1 = new CButton(130+3, 120+3, BUTTON_QUIT, CInterface::InterfaceControl.Surf_MenuButton);

    if(pButton1 != NULL)
    {
        CButton::ButtonList.push_back(pButton1);
    }
}

bool CButtonPanel::AddButtonToInterface(CButton* pButton, int mX, int mY)
{
    for(int i=0; i<MAX_BUTTON_SLOTS; ++i)
    {
        if(ButtonSlot[i] == pButton) //fisrt we need to clear old positions of our moved button IF  HE WAS  ON PANEL BUTTTON
            ButtonSlot[i] = NULL;

        if( ( mX > nPosX + 33*i +3 ) && ( mX < nPosX + 33*i +3 + 30) && ( mY > nPosY + 3 ) && ( mY < nPosY + 3 + 30 ) )
        {
            ButtonSlot[i] = pButton;
            return true;
        }
    }
    return false;
}

void CButtonPanel::DeleteMovedButtons()
{
    for(int i=0; i<MAX_BUTTON_SLOTS; ++i)
    {
        if(!ButtonSlot[i]) continue;

        if(ButtonSlot[i]->GetButtonState() == BUTTONSTATE_MOVED)
            ButtonSlot[i] = NULL;
    }
}
