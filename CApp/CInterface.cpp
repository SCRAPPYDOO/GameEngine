#include "CInterface.h"
#include "CUnitInfoPanel.h"
#include "CInterfaceBag.h"

CInterface CInterface::InterfaceControl;

CInterface::CInterface() 
{
	for(int i=0; i<MAX_INTERFACEOBJECTS; ++i)
	{
		Interface[i] = NULL;
	}
}

CInterface::CInterface(InterfaceType eType)
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

bool CInterface::OnLoad()
{
    char* SurfName = "./error/surf_error.png";

    //ToDo: Load cfg from file
    switch(eInterfaceType)
    {
        case INTERFACE_MAINMENU:
        {
            nWidht = INTERFACE_MAINMENU_W;
            nHeight = INTERFACE_MAINMENU_H;
            SurfName = "./menu/main_menu_surf.png"; break;
        }
        case INTERFACE_PLAYERINFO: SurfName = "./interface/interface_unitinfo_surf.png"; break;
        case INTERFACE_BUTTON_PANEL: 
        {
            nWidht = INTERFACE_BUTTON_PANEL_W;
            nHeight = INTERFACE_BUTTON_PANEL_H;
            SurfName = "./interface/interface_button_surf.png"; break;
        }
        case INTERFACE_GAMEMENU: 
        {
            nWidht = INTERFACE_GAMEMENU_W;
            nHeight = INTERFACE_GAMEMENU_H;
            SurfName = "./menu/menu_gamebackground.png"; break;
        }
        case INTERFACE_CHARACTERPANEL: 
        {
            nWidht = INTERFACE_CHARACTERPANEL_W;
            nHeight = INTERFACE_CHARACTERPANEL_H; 
            SurfName = "./interface/surf_character_panel.png"; break;
        }
        case INTERFACE_BAG: SurfName = "./interface/interface_equpment_surf.png"; break;
        case INTERFACE_LOOT:
        {
            nWidht = INTERFACE_LOOT_W_H;
            nHeight = INTERFACE_LOOT_W_H; 
            SurfName = "./interface/interface_loot_surf.png"; break;
        }
        default: break;
    }

    if((Surf_Interface = CSurface::OnLoad(SurfName)) == NULL) 
        return false;

    LoadButtons();

    return true;
}

void CInterface::OnLoop()
{
    UpdateButtonsPosition();
}

void CInterface::OnRender(SDL_Surface* Surf_Display)
{
	if(Surf_Interface == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Interface, nPosX, nPosY);

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        ButtonsList[i]->OnRender(Surf_Display);
    }
}

void CInterface::OnCleanup()
{
	if(Surf_Interface) 
		SDL_FreeSurface(Surf_Interface);

	Surf_Interface = NULL;

    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        ButtonsList[i]->OnCleanup();
    }

    ButtonsList.clear();
}

bool CInterface::LoadInterface()
{
    CleanUpInterface();

    switch(CApp::eGameState)
    {
        case MAIN_MENU:
        {
            if(LoadInterface(INTERFACE_MAINMENU) == false)
                return false;

            break;
        }

        case TEST:
        {
            InterfaceType eType;

            for(int i=0; i<4; ++i)
            {
                switch(i)
                {
                    case 0: eType = INTERFACE_PLAYERINFO; break;      
                    case 1: eType = INTERFACE_BUTTON_PANEL; break;           
                    case 2: eType = INTERFACE_CHARACTERPANEL; break;
                    case 3: eType = INTERFACE_LOOT          ; break;
                    default: break;
                }

                if(LoadInterface(eType) == false)
                    return false;
            }

            break;
        }

        default: return false;
    }

	return true;
}

bool CInterface::LoadInterface(InterfaceType eType)
{
    CInterface* pInterface = NULL;

    switch(eType)
    {
        case INTERFACE_MAINMENU: pInterface = new CInterface(eType); break;
        case INTERFACE_PLAYERINFO: pInterface = new CUnitInfoPanel(); break;
        case INTERFACE_BUTTON_PANEL: pInterface = new CInterface(eType); break;
        case INTERFACE_GAMEMENU: pInterface = new CInterface(eType); break;
        case INTERFACE_CHARACTERPANEL: pInterface = new CInterface(eType); break;
        case INTERFACE_BAG: pInterface = new CInterfaceBag(); break;
        case INTERFACE_LOOT: pInterface = new CInterface(eType); break;
        default: return false;
    }

    if(pInterface && pInterface->OnLoad() == false)
        return false;

	Interface[eType] = pInterface;

    return true;
}

CInterface* CInterface::GetInterface(int nPosX, int nPosY)
{
	for(int i = 0; i < MAX_INTERFACEOBJECTS; i++) 
    {   
        if(!Interface[i]) continue;
                
        if( ( nPosX > Interface[i]->GetPosX() ) && ( nPosX < Interface[i]->GetPosX() + Interface[i]->GetWidht()) && ( nPosY > Interface[i]->GetPosY() ) && ( nPosY < Interface[i]->GetPosY() + Interface[i]->GetHeight() ) )
        {
            return Interface[i];
        }
    }

    return NULL;
}

void CInterface::CleanUpInterface()
{
	for(int i = 0;i < MAX_INTERFACEOBJECTS;i++) 
    {
        if(!Interface[i]) continue;

        Interface[i]->OnCleanup();
		Interface[i] = NULL;
    }
}

void CInterface::CleanUpInterface(InterfaceType eType)
{	
	if(Interface[eType] == NULL)
		return;

	Interface[eType]->OnCleanup();
	Interface[eType] = NULL; 
}

bool CInterface::IsInterfaceOnPos(int nX, int nY)
{
    if( ( nX > nPosX ) && ( nX < nPosX + nWidht) && ( nY > nPosY ) && ( nY < nPosY + nHeight ) )
        return true;

    return false;
}

void CInterface::OnMove(int nNextX, int nNextY) 
{ 
    OldX = nPosX;
    OldY = nPosY;

    nPosX = nNextX - nDistX; 
    nPosY = nNextY - nDistY;   
}   

void CInterface::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        ButtonsList[i]->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
    }
}

void CInterface::UpdateButtonsPosition()
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

void CInterface::LoadButtons()
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

        case INTERFACE_LOOT:
        {
            for(int i=0; i<3; ++i)
            {
                switch(i)
                {
                    case 0: eType = BUTTON_LOOT_QUIT; x = nPosX + INTERFACE_LOOT_W_H - 30; y = nPosY; break;
                    case 1: eType = BUTTON_LOOT_LOOTALL; x = nPosX; y = nPosY + INTERFACE_LOOT_W_H - 30; break;
                    case 2: eType = BUTTON_SWORD;  x = nPosX; y = nPosY + INTERFACE_LOOT_W_H - 70; break;
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

CButton* CInterface::GetButton(int nPosX, int nPosY) const
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        if(ButtonsList[i]->IsButtonOnPos(nPosX, nPosY))
            return ButtonsList[i];
    }

    return NULL;
}

void CInterface::DeleteButtonFromSlot(CButton* pButton)
{
    for(int i = 0;i < ButtonsList.size();i++) 
    {   
        if(!ButtonsList[i]) continue;

        if(ButtonsList[i] == pButton)
            ButtonsList[i] = NULL;
    }
}

bool CInterface::AddButtonToSlot(CButton* pButton, int mX, int mY)
{
    switch(eInterfaceType)
    {
        case INTERFACE_EQUIP: // wybierz switchem type itemu i wloz go tam gdzie jego miesce
        case INTERFACE_LOOT:
        case INTERFACE_BAG:
        {
            if(pButton->GetButtonClass() == BUTTONCLASS_SHORTCURT || pButton->GetButtonClass() == BUTTONCLASS_SPELL)
                return false;

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
                    //If there is button on slot we need to remove him
                    if(CButton* pOtherButton = GetButton(mX, mY))
                    {
                        pOtherButton->OnCleanup();
                        DeleteButtonFromSlot(pOtherButton);
                    }

                    if(pButton->GetButtonClass() == BUTTONCLASS_SHORTCURT)
                    {
                        pButton->SetPositionX(nPosX + 33*i +3);
                        pButton->SetPositionY(nPosY + 3);
                        ButtonsList.push_back(pButton);
                        return true;
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

        default: return false;
    }
}