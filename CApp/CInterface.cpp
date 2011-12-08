#include "CInterface.h"

CInterface::CInterface() 
{

}

CInterface::CInterface(InterfaceType eType)
{
    nPosX = 0;
    nPosY = 0;
    nWidht = 0;  
    nHeight = 0;

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
			nPosX = 0;
			nPosY = 0;
            nWidht = INTERFACE_MAINMENU_W;
            nHeight = INTERFACE_MAINMENU_H;
            SurfName = "./menu/main_menu_surf.png"; break;
        }
        case INTERFACE_PLAYERINFO:
        {
            nPosX = 0.5 * WWIDTH - 0.5 * INTERFACE_PLAYERINFO_W;
            nPosY = WHEIGHT - INTERFACE_PLAYERINFO_H;
            nWidht = INTERFACE_PLAYERINFO_W;
            nHeight = INTERFACE_PLAYERINFO_H;
            SurfName = "./interface/Panel.png"; break;
        }
        case INTERFACE_GAMEMENU: 
        {
            nPosX = 0.5 * WWIDTH - 0.5 * INTERFACE_GAMEMENU_W;
            nPosY = 0.5 * WHEIGHT - 0.5 * INTERFACE_GAMEMENU_H;
            nWidht = INTERFACE_GAMEMENU_W;
            nHeight = INTERFACE_GAMEMENU_H;
            SurfName = "./menu/menu_gamebackground.png"; break;
        }
        case INTERFACE_CHARACTERPANEL: 
        {
            nPosX = 0.5 * WWIDTH - 0.5 * INTERFACE_CHARACTERPANEL_W;
            nPosY = 0;
            nWidht = INTERFACE_CHARACTERPANEL_W;
            nHeight = INTERFACE_CHARACTERPANEL_H; 
            SurfName = "./interface/surf_character_panel.png"; break;
        }
        case INTERFACE_EQUIP:
        {
            nPosX = 0.5 * WWIDTH - 0.5 * INTERFACE_EQUIPMENT_W;
            nPosY = 0.5 * WHEIGHT - 0.5 * INTERFACE_EQUIPMENT_H;
            nWidht = INTERFACE_EQUIPMENT_W;
            nHeight = INTERFACE_EQUIPMENT_H;
            SurfName = "./interface/interface_equpment_surf.png"; break;
        }
        case INTERFACE_LOOT:
        {
            nPosX = 1000;
            nPosY = 0;
            nWidht = INTERFACE_LOOT_W_H;
            nHeight = INTERFACE_LOOT_W_H; 
            SurfName = "./interface/interface_loot_surf.png"; break;
        }
        case INTERFACE_SPELLBOOK:
        {
            nPosX = 0.5 * WWIDTH - 0.5 * INTERFACE_SPELLBOOK_W;
            nPosY = 0.5 * WHEIGHT - 0.5 * INTERFACE_SPELLBOOK_H;
            nWidht = INTERFACE_SPELLBOOK_W;
            nHeight = INTERFACE_SPELLBOOK_H; 
            SurfName = "./interface/interface_loot_surf.png"; break;
        }
        case INTERFACE_MASAGEWINDOW:
        {
            nPosX = 50;
            nPosY = 400;
            nWidht = 100;
            nHeight = 100; 
            SurfName = "./interface/interface_massagewindow_surf.png"; break;
        }
        case INTERFACE_CHARACTERSHEET:
        {
            nPosX = 0.5 * WWIDTH - 0.5 * INTERFACE_CHARACTERSHEET_W;
            nPosY = 0.5 * WHEIGHT - 0.5 * INTERFACE_CHARACTERSHEET_H;
            nWidht = INTERFACE_CHARACTERSHEET_W;
            nHeight = INTERFACE_CHARACTERSHEET_H; 
            SurfName = "./interface/interface_charactersheet_surf.png"; break;
        }
        case INTERFACE_CHARACTERCREATOR:
        {
            SurfName = "./interface/interface_character_creator.png"; break;
        }
        case INTERFACE_INFOWINDOW:
        {
            nPosX = 800;
            nPosY = 800;
            nWidht = 10;
            nHeight = 10;     
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
                    case 2: eType = BUTTON_MENU_CREATECHARACTER; break;
                    default: break;
				}
					
                x = nPosX + 640;
                y = nPosY + 300 + i*40;

				CButton *pButton = new CButton(x, y, eType);

                if(pButton->OnLoad() == false)
					return;

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
                    case 1: eType = BUTTON_CHARPANEL_EQUIPMENT; break;
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

        case INTERFACE_EQUIP:
		{
			for(int i=0; i<1; ++i)
			{
				switch(i)
				{
					case 0: eType = BUTTON_EQUIPMENT_QUIT; x = nPosX + nWidht - 30; y = nPosY; break;

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
            for(int i=0; i<2; ++i)
            {
                switch(i)
                {
                    case 0: eType = BUTTON_LOOT_QUIT; x = nPosX + INTERFACE_LOOT_W_H - 30; y = nPosY; break;
                    case 1: eType = BUTTON_LOOT_LOOTALL; x = nPosX; y = nPosY + INTERFACE_LOOT_W_H - 30; break;
                    default: break;
                }

                CButton *pButton = new CButton(x, y, eType);

                if(pButton->OnLoad() == false)
                    break;

                ButtonsList.push_back(pButton);
            }
            break;
        }

        case INTERFACE_SPELLBOOK:
        {
            for(int i=0; i<1; ++i)
            {
                switch(i)
                {
                    case 0: eType = BUTTON_SPELLBOOK_QUIT; x = nPosX + INTERFACE_SPELLBOOK_W - 30; y = nPosY; break;

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
		case INTERFACE_EQUIP:
		{


		}




        //case INTERFACE_BUTTON_PANEL:
        //{
        //    for(int i=0; i<INTERFACE_BUTTON_PANEL_MAXSLOTS; ++i)
        //    {
        //        if( ( mX > nPosX + 33*i +3 ) && ( mX < nPosX + 33*i +3 + 30) && ( mY > nPosY + 3 ) && ( mY < nPosY + 3 + 30 ) )
        //        {
        //            //If there is button on slot we need to remove him
        //            if(CButton* pOtherButton = GetButton(mX, mY))
        //            {
        //                pOtherButton->OnCleanup();
        //                DeleteButtonFromSlot(pOtherButton);
        //            }

        //            if(pButton->GetButtonClass() == BUTTONCLASS_SHORTCURT)
        //            {
        //                pButton->SetPositionX(nPosX + 33*i +3);
        //                pButton->SetPositionY(nPosY + 3);
        //                ButtonsList.push_back(pButton);
        //                return true;
        //            }

        //            CButton* pShortcut = new CButton(nPosX + 33*i +3,  nPosY + 3, pButton->GetButtonType());
        //        
        //            if(!pShortcut || !pShortcut->OnLoad())
        //                return false;

        //            pShortcut->SetButtonClass(BUTTONCLASS_SHORTCURT);

        //            ButtonsList.push_back(pShortcut);
        //            return false;
        //        }
        //    }

        //    return false;
        //}

        default: return false;
    }
}