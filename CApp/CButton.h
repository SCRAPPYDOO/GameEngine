#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <vector>

#include "CSurface.h"
#include "CInterface.h"

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
        ~CButton() {}

		static std::vector<CButton*>    ButtonList;
	
	private:
		ButtonType eType;
		int x;
        int y;
        int w;
        int h;

	public:
		bool OnLoad(ButtonType eType);

		void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();
};

#endif