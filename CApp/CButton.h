#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <vector>

#include "CSurface.h"

enum ButtonType
{
	BUTTON_DEFAULT	= 0,
	BUTTON_PLAY		= 1,
	BUTTON_QUIT		= 2,
};

class CButton
{
	public:
		CButton();

		static std::vector<CButton*>    ButtonList;

		SDL_Surface* Surf_Button;
		
	public:
		ButtonType eType;
		int x;
        int y;
        int w;
        int h;

	public:
		void OnLoad(ButtonType eType);

		void OnRender(SDL_Surface* Surf_Display);
};

#endif