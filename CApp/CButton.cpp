#include "CButton.h"

CButton CButton::ButtonControl;
std::vector<CButton*> CButton::ButtonList;

CButton::CButton()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;

    pButtonSurface = NULL;

	eType = BUTTON_DEFAULT;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

CButton::CButton(int nPosX, int nPosY, ButtonType Type, SDL_Surface* pSurface)    //Used by button panel on create
{
	x = nPosX;
	y = nPosY;
	w = 30;
	h = 30;

    pButtonSurface = pSurface;

	eType = Type;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

bool CButton::OnLoad(ButtonType eType)
{
    pButtonSurface = CInterface::InterfaceControl.Surf_MenuButton;

	switch(eType)
	{
		case BUTTON_PLAY:
		{
			this->x = 640;
			this->y = 300;
			this->w = 134;
			this->h = 30;

			break;
		}

        case BUTTON_QUIT:
        {
			this->x = 640;
			this->y = 350;
			this->w = 134;
			this->h = 30;

			break;
		}

        case BUTTON_MENU:
        {
            this->x = 1050;
			this->y = 16;
			this->w = 134;
			this->h = 30;
            break;
        }

        case BUTTON_GAMEMENU_QUIT: x = 400; y = 200; w = 134; h = 30; break;
        case BUTTON_GAMEMENU_RETURN: x = 400; y = 400; w = 134; h = 30; break;

		default: break;
	}

    this->eType = eType;

    return true;
}

void CButton::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Display == NULL || pButtonSurface == NULL)
        return;
	
    CSurface::OnDraw(Surf_Display, pButtonSurface, x, y, w*eAnimationState, 0, w, h);
}

void CButton::OnCleanup()
{
    /*
    if(pButtonSurface != NULL)
		SDL_FreeSurface(pButtonSurface);

    pButtonSurface = NULL;
    */
}

void CButton::Activate()
{
    eAnimationState = BUTTON_ANIME_ONCLICK;

    switch(eType)
	{
		case BUTTON_PLAY:
		{
            CApp::eGameState = TEST;

            CInterface::InterfaceControl.LoadInterface();

            if(CArea::AreaControl.OnLoad("./maps/1.area") == false) 
                break;

			break;
		}

        case BUTTON_QUIT:
        {
            CInterface::InterfaceControl.CleanUpInterface();
            CApp::eGameState = MAIN_MENU;
            CInterface::InterfaceControl.LoadButtons();
            break;
		}

        case BUTTON_MENU: //in game button menu
        {
            if(!CInterface::IsGameMenu)
            {
                CInterface::InterfaceControl.LoadInterface(INTERFACE_GAMEMENU);
                CInterface::IsGameMenu = true;
            }

            break;
        }

        case BUTTON_GAMEMENU_RETURN: // ingame game menu button return
        {
            CInterface::InterfaceControl.UnloadInterface(INTERFACE_GAMEMENU);
            CInterface::IsGameMenu = false;

            break;
        }

		default: break;
	}
}

CButton* CButton::GetButton(int nX, int nY)
{
    CButton* pButton = NULL;

    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if(ButtonList[i]->IsButtonOnPos(nX,nY))
        {
            pButton = ButtonList[i];
            break;
        }
    }

    return pButton;
}

bool CButton::IsButtonOnPos(int mX, int mY)
{
    if( ( mX > x ) && ( mX < x + w) && ( mY > y ) && ( mY < y + h ) )
        return true;

    return false;
}

void CButton::OnDrop(int mX, int mY)
{
    //sprawdz czy zadne button panel nie ejst w pioblizu
    for(int i = 0; i < CInterface::InterfaceObjectList.size(); i++) 
    {   
        if(!CInterface::InterfaceObjectList[i]) continue;
                
        if(CInterface::InterfaceObjectList[i]->IfInterfaceOnPos(mX,mY))
           if(CInterface::InterfaceObjectList[i]->GetInterfaceType() == INTERFACE_BUTTON_PANEL)
                if(CInterface::InterfaceObjectList[i]->AddButtonToInterface(this, mX, mY))
                    return;
    }

    CButton::ButtonControl.DeleteButton(this);
}

void CButton::DeleteButton(CButton* pButton)
{
    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if(ButtonList[i] == pButton)
        {
            ButtonList[i]->OnCleanup();
            ButtonList[i] = NULL;
            break;
        }
    }
}

void CButton::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(Left)  //if we move something dont set animation
        return;

    //Set Proper Animation
    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if(ButtonList[i]->IsButtonOnPos(mX,mY))
        {
            ButtonList[i]->eAnimationState = BUTTON_ANIME_ONMOTION;
        }
        else
        {
            ButtonList[i]->eAnimationState = BUTTON_ANIME_NORMAL;
        }  
    }
}

