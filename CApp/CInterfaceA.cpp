#include "CInterfaceA.h"

CInterfaceA::CInterfaceA()
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

CInterfaceA::CInterfaceA(InterfaceType eType)
{
    nPosX = 50;
    nPosY = 50;
    nWidht = 50;  
    nHeight = 50;

    OldX = 0;
    OldY = 0;

    Surf_Interface = NULL;
    eInterfaceType = eType;
}

void CInterfaceA::OnCleanup()
{
    CInterface::OnCleanup();

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        for(int n = 0;n < CButton::ButtonList.size();n++) 
        {   
            if(!CButton::ButtonList[n]) continue;

            if(CButton::ButtonList[n] == ButtonsList[i])
            {
                CButton::ButtonList[n]->OnCleanup();
                CButton::ButtonList[n] = NULL;  
            }
        }

        ButtonsList[i]->OnCleanup();
        ButtonsList[i] = NULL;
    }

    ButtonsList.clear();
}

void CInterfaceA::UpdateButtonsPosition()
{
    if(OldX == 0 && OldY == 0)
        return;

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;
                
        ButtonsList[i]->OnMoveWithInterface(nPosX-OldX,nPosY-OldY);
    }

    OldX = 0;
    OldY = 0;
}

void CInterfaceA::LoadButtons()
{
    ButtonType eType = BUTTON_DEFAULT;

    switch(eInterfaceType)
    {
        case INTERFACE_MAINMENU:
		{
			for(int i=0; i<2; ++i)
			{
                CButton *pButton = new CButton();

				switch(i)
				{
					case 0: eType = BUTTON_PLAY; break;
					case 1: eType = BUTTON_QUIT; break;
                    case 2: eType = BUTTON_CREATECHARACTER; break;
                    default: break;
				}
					
				if(pButton->OnLoad(eType) == false)
                    break;

                ButtonsList.push_back(pButton);
				CButton::ButtonList.push_back(pButton);
			}

			break;
		}

        case INTERFACE_GAMEMENU:
        {
            for(int i=10; i<12; ++i)
            {
                CButton *pButton = new CButton();

                switch(i)
                {
                    case 10: eType = BUTTON_GAMEMENU_QUIT; break;
                    case 11: eType = BUTTON_GAMEMENU_RETURN; break;
                    default: break;
                }

                if(pButton->OnLoad(eType) == false)
                    break;

                ButtonsList.push_back(pButton);
		        CButton::ButtonList.push_back(pButton);
            }

            break;
        }

        case INTERFACE_CHARACTERPANEL:
        {
            for(int i=20; i<25; ++i)
            {
                CButton *pButton = new CButton();

                switch(i)
                {
                    case 20: eType = BUTTON_CHARPANEL_CHARSHEET; break;
                    case 21: eType = BUTTON_CHARPANEL_EQUPMENT; break;
                    case 22: eType = BUTTON_CHARPANEL_SPELLBOOK; break;
                    case 23: eType = BUTTON_CHARPANEL_QUESTDIARY; break;
                    case 24: eType = BUTTON_CHARPANEL_GAMEMENU; break;
                }

                if(pButton->OnLoad(eType) == false)
                    break;
 
                ButtonsList.push_back(pButton);
		        CButton::ButtonList.push_back(pButton);
            }

            break;
        }

        default: break;
    }
}