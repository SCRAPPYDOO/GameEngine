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

void CButton::OnLoad(ButtonType eType)
{
	switch(eType)
	{
		case BUTTON_PLAY:
		{
			Surf_Button = CSurface::OnLoad("./menu/button_menu.png");
			x = 640;
			y = 300;
			w = 134;
			h = 29;

			break;
		}

		default: break;
	}
}

void CButton::OnRender(SDL_Surface* Surf_Display)
{
	CSurface::OnDraw(Surf_Display, Surf_Button, 0, 0);
}

