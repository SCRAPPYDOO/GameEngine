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

CButton::CButton(int nValueX, int nValueY, ButtonType Type, SDL_Surface* pSurface)    //Used by button panel on create
{
	x = nValueX;
	y = nValueY;

	w = 30;
	h = 30;

    this->pButtonSurface = NULL;
    this->pButtonSurface = pSurface;

	eType = Type;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

bool CButton::OnLoad(ButtonType eType)
{
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

		default: break;
	}

    this->eType = eType;

    return true;
}

void CButton::OnRender(SDL_Surface* Surf_Display)
{
	CSurface::OnDraw(Surf_Display, pButtonSurface, x, y, w*eAnimationState, h*static_cast<int>(eType), w, h);
}

void CButton::OnCleanup()
{

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

		default: break;
	}
}

CButton* CButton::GetButton(int nX, int nY)
{
    CButton* pButton = NULL;

    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if( ( nX > ButtonList[i]->GetPosX() ) && ( nX < ButtonList[i]->GetPosX() + ButtonList[i]->GetWidht()) && ( nY > ButtonList[i]->GetPosY() ) && ( nY < ButtonList[i]->GetPosY() + ButtonList[i]->GetHeight() ) )
        {
            pButton = ButtonList[i];
            break;
        }
    }

    return pButton;
}

void CButton::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if( ( mX > ButtonList[i]->GetPosX() ) && ( mX < ButtonList[i]->GetPosX() + ButtonList[i]->GetWidht()) && ( mY > ButtonList[i]->GetPosY() ) && ( mY < ButtonList[i]->GetPosY() + ButtonList[i]->GetHeight() ) )
        {
            ButtonList[i]->eAnimationState = BUTTON_ANIME_ONMOTION;
        }
        else
        {
            ButtonList[i]->eAnimationState = BUTTON_ANIME_NORMAL;
        }
           
    }
}
