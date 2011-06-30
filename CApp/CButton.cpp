#include "CButton.h"

std::vector<CButton*> CButton::ButtonList;

CButton::CButton()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;

    pButtonSurface = NULL;

	eType = BUTTON_DEFAULT;
    nAnimationState = 0;
}

CButton::CButton(int nValueX, int nValueY, ButtonType Type, SDL_Surface* pButtonSurface)    //Used by button panel on create
{
	x = nValueX;
	y = nValueY;

	w = 30;
	h = 30;

    this->pButtonSurface = pButtonSurface;

	eType = Type;
    nAnimationState = 0;
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
	CSurface::OnDraw(Surf_Display, pButtonSurface, x, y, w*nAnimationState, h*static_cast<int>(eType), w, h);
}

void CButton::Activate()
{
    nAnimationState = 2;

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