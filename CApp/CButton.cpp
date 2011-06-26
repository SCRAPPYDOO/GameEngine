#include "CButton.h"

std::vector<CButton*> CButton::ButtonList;

CButton::CButton()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->eType = BUTTON_DEFAULT;
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

    return true;
}

void CButton::OnRender(SDL_Surface* Surf_Display)
{
	CSurface::OnDraw(Surf_Display, CInterface::Surf_MenuButton, x, y, 0, 0, w, h);
}

void CButton::OnCleanup()
{
}