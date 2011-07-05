#include "CButtonPanel.h"

CButtonPanel::CButtonPanel()
{
    nPosX               = 300;
    nPosY               = 600;
    nWidht              = 600;
    nHeight             = 60;

    Surf_Interface      = NULL;
    eInterfaceType      = INTERFACE_BUTTON_PANEL;

    for(int i=0; i<MAX_BUTTON_SLOTS; ++i)
    {
        ButtonSlot[i] = NULL;
    }
}

bool CButtonPanel::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CButtonPanel::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);
}

void CButtonPanel::OnCleanup()
{
    CInterface::OnCleanup();

    for(int i=0;i < MAX_BUTTON_SLOTS; ++i)
    {
        ButtonSlot[i] = NULL;
    }
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
