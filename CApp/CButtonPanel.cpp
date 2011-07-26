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

    for(int i = 0;i < MAX_BUTTON_SLOTS;i++) 
    {   
        if(!ButtonSlot[i]) continue;
                
        ButtonSlot[i]->OnRender(Surf_Display);
    }
}

void CButtonPanel::OnCleanup()
{
    CInterface::OnCleanup();

    for(int i=0;i < MAX_BUTTON_SLOTS; ++i)
    {
        if(!ButtonSlot[i]) continue;

        ButtonSlot[i]->OnCleanup();
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

bool CButtonPanel::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
    //Always return false because we only create a shortcut to button, item, spell
    for(int i=0; i<MAX_BUTTON_SLOTS; ++i)
    {
        if( ( mX > nPosX + 33*i +3 ) && ( mX < nPosX + 33*i +3 + 30) && ( mY > nPosY + 3 ) && ( mY < nPosY + 3 + 30 ) )
        {
            if(ButtonSlot[i] == NULL)
            {
                CButton* pShortcut = new CButton(nPosX + 33*i +3,  nPosY + 3, pButton->GetButtonType());
                
                if(!pShortcut || !pShortcut->OnLoad())
                    return false;

                pShortcut->SetButtonClass(BUTTONCLASS_SHORTCURT);

                ButtonSlot[i] = pShortcut;

                return false;
            }
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

void CButtonPanel::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    for(int i=0; i<MAX_BUTTON_SLOTS; ++i) 
    {   
        if(!ButtonSlot[i]) continue;

        ButtonSlot[i]->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
    }
}

CButton* CButtonPanel::GetButton(int nPosX, int nPosY) const
{
    for(int i = 0;i < MAX_BUTTON_SLOTS;i++) 
    {   
        if(!ButtonSlot[i]) continue;

        if(ButtonSlot[i]->IsButtonOnPos(nPosX, nPosY))
            return ButtonSlot[i];
    }

    return NULL;
}