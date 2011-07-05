#include "CCharacterPanel.h"

CCharacterPanel::CCharacterPanel()
{
    nPosX = 700;
    nPosY = 500;
    nWidht = 200;  
    nHeight = 200;

    OldX = OldY = 0;

    Surf_Interface = NULL;
    eInterfaceType = INTERFACE_CHARACTERPANEL;

    for(int i=0; i<MAX_BUTTON_LIST; ++i)
    {
        ButtonList[i] = NULL;
    }
}

bool CCharacterPanel::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    for(int i=20; i<24; ++i)
    {
        ButtonType eType = BUTTON_DEFAULT;

        switch(i)
        {
            case 20: eType = BUTTON_CHARPANEL_CHARSHEET; break;
            case 21: eType = BUTTON_CHARPANEL_EQUPMENT; break;
            case 22: eType = BUTTON_CHARPANEL_SPELLBOOK; break;
            case 23: eType = BUTTON_CHARPANEL_QUESTDIARY; break;
        }

        CButton *pButton = new CButton();

        if(pButton->OnLoad(eType) == false)
            return false;
 
        int n = i - 20;

        ButtonList[n] = pButton;
		CButton::ButtonList.push_back(pButton);
    }

    return true;
}

void CCharacterPanel::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);
}

void CCharacterPanel::OnCleanup()
{
    CInterface::OnCleanup();

    for(int i = 0;i < MAX_BUTTON_LIST;i++) 
    {   
        if(!ButtonList[i]) continue;

        for(int n = 0;n < CButton::ButtonList.size();n++) 
        {   
            if(!CButton::ButtonList[n]) continue;

            if(CButton::ButtonList[n] == ButtonList[i])
            {
                CButton::ButtonList[n]->OnCleanup();
                CButton::ButtonList[n] = NULL;  
            }
        }

        ButtonList[i]->OnCleanup();
        ButtonList[i] = NULL;
    }
}

void CCharacterPanel::UpdateButtonsPosition()
{
    if(OldX == 0 && OldY == 0)
        return;

    for(int i = 0;i < MAX_BUTTON_LIST;i++) 
    {   
        if(!ButtonList[i]) continue;
                
        ButtonList[i]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
    }

    OldX = 0;
    OldY = 0;
}
