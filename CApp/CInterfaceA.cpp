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

void CInterfaceA::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        ButtonsList[i]->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
    }
}

void CInterfaceA::OnRender(SDL_Surface* Surf_Display)
{
    CInterface::OnRender(Surf_Display);

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        ButtonsList[i]->OnRender(Surf_Display);
    }
}

void CInterfaceA::OnCleanup()
{
    CInterface::OnCleanup();

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

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

    int x = 0;
	int y = 0;

    switch(eInterfaceType)
    {
        case INTERFACE_MAINMENU:
		{
			for(int i=0; i<3; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_PLAY; break;
					case 1: eType = BUTTON_QUIT; break;
                    case 2: eType = BUTTON_CREATECHARACTER; break;
                    default: break;
				}
					
                x = nPosX + 640;
                y = nPosY + 300 + i*40;

				CButton *pButton = new CButton(x, y, eType);

                if(pButton->OnLoad() == false)
                    break;

                ButtonsList.push_back(pButton);
			}

			break;
		}

        case INTERFACE_GAMEMENU:
        {
            for(int i=0; i<2; ++i)
            {
                switch(i)
                {
                    case 0: eType = BUTTON_GAMEMENU_QUIT; break;
                    case 1: eType = BUTTON_GAMEMENU_RETURN; break;
                    default: break;
                }

                x = nPosX + 100;
                y = nPosY + 100 + i*40;

				CButton *pButton = new CButton(x, y, eType);

                if(pButton->OnLoad() == false)
                    break;

                ButtonsList.push_back(pButton);
            }

            break;
        }

        case INTERFACE_CHARACTERPANEL:
        {
            for(int i=0; i<5; ++i)
            {
                switch(i)
                {
                    case 0: eType = BUTTON_CHARPANEL_CHARSHEET; break;
                    case 1: eType = BUTTON_CHARPANEL_EQUPMENT; break;
                    case 2: eType = BUTTON_CHARPANEL_SPELLBOOK; break;
                    case 3: eType = BUTTON_CHARPANEL_QUESTDIARY; break;
                    case 4: eType = BUTTON_CHARPANEL_GAMEMENU; break;
                }

                x = nPosX + 5 + i * 33;
                y = nPosY + 5;

				CButton *pButton = new CButton(x, y, eType);

                if(pButton->OnLoad() == false)
                    break;
 
                ButtonsList.push_back(pButton);
            }

            break;
        }

        case INTERFACE_BAG:
		{
			for(int i=0; i<5; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_BAG_QUIT; x = nPosX + nWidht - 30; y = nPosY; break;
                    case 1: eType = BUTTON_BAG_SLOT_ONE; x = nPosX + i * 33; y = nPosY; break;
                    case 2: eType = BUTTON_BAG_SLOT_TWO; x = nPosX + i*33; y = nPosY; break;
                    case 3: eType = BUTTON_BAG_SLOT_THREE; x = nPosX + i*33; y = nPosY; break;
                    case 4: eType = BUTTON_BAG_SLOT_FOUR; x = nPosX + i*33; y = nPosY; break;

                    default: break;
				}
					
                CButton *pButton = new CButton(x, y, eType);

				if(pButton->OnLoad() == false)
                    break;

                ButtonsList.push_back(pButton);
			}

			break;
		}

        default: break;
    }
}

CButton* CInterfaceA::GetButton(int nPosX, int nPosY) const
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        if(ButtonsList[i]->IsButtonOnPos(nPosX, nPosY))
            return ButtonsList[i];
    }

    return NULL;
}

void CInterfaceA::DeleteButtonFromSlot(CButton* pButton)
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        if(ButtonsList[i] == pButton)
            ButtonsList[i] = NULL;
    }
}

bool CInterfaceA::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
    switch(eInterfaceType)
    {
        case INTERFACE_EQUIP: // wybierz switchem type itemu i wloz go tam gdzie jego miesce
        case INTERFACE_LOOT:
        case INTERFACE_BAG:
        {
            for(int x = 0; x < INTERFACE_BAG_MAXSLOT_X; ++x) 
            {   
                for(int y = 0; y < INTERFACE_BAG_MAXSLOT_Y; ++y) 
                {   
                    if( ( mX > nPosX + 10 + x*33 ) && ( mX < nPosX + 10 + x*33 + 30) && ( mY > nPosY + 100 + y*33 ) && ( mY < nPosY + 100 + y*33 + 30 ) )
                    {
                        //ToDo: Need to check if on slot  is any aother button then return false
                        if(CButton *Button = GetButton(mX, mY))
                            if(Button)
                                return false;

                        pButton->SetPositionX(nPosX + 10 + x*33);
                        pButton->SetPositionY(nPosY + 100 + y*33);
                        ButtonsList.push_back(pButton);
                        return true;
                    }
                }
            }

            return false;
        }

        case INTERFACE_BUTTON_PANEL:
        {
            for(int i=0; i<INTERFACE_BUTTON_PANEL_MAXSLOTS; ++i)
            {
                if( ( mX > nPosX + 33*i +3 ) && ( mX < nPosX + 33*i +3 + 30) && ( mY > nPosY + 3 ) && ( mY < nPosY + 3 + 30 ) )
                {
                    if(CButton* pButton = GetButton(mX, mY))
                    {
                        pButton->OnCleanup();
                        DeleteButtonFromSlot(pButton);
                    }

                    CButton* pShortcut = new CButton(nPosX + 33*i +3,  nPosY + 3, pButton->GetButtonType());
                
                    if(!pShortcut || !pShortcut->OnLoad())
                        return false;

                    pShortcut->SetButtonClass(BUTTONCLASS_SHORTCURT);

                    ButtonsList.push_back(pShortcut);
                    return false;
                }
            }

            return false;
        }

        default:
        {
            if(CButton *Button = GetButton(mX, mY))
                if(Button != NULL)
                    return false;

            ButtonsList.push_back(pButton);
            return true;
        }
    }
}