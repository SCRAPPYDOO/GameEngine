#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <vector>

#include "CSurface.h"
#include "CInterface.h"

enum ButtonType
{
	BUTTON_DEFAULT	= 99,
	BUTTON_PLAY		= 0,
	BUTTON_QUIT		= 1,

    BUTTON_GAMEMENU_QUIT = 10,
    BUTTON_GAMEMENU_RESUME = 11,
};

class CButton
{
	public:
		CButton();
        CButton(int nValueX, int nValueY, ButtonType Type, SDL_Surface* pButtonSurface);

        ~CButton() {}

		static std::vector<CButton*>    ButtonList;
	
	private:
        SDL_Surface* pButtonSurface;

		ButtonType eType;

		int x;
        int y;
        int w;
        int h;
        int nAnimationState;

	public:
		bool OnLoad(ButtonType eType);

		void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        int GetPosX() { return x; }
        int GetPosY() { return y; }
        int GetPosW() { return w; }
        int GetPosH() { return h; }

        void SetPositionX(int nValue) { x = nValue;}
        void SetPositionY(int nValue) { y = nValue;}

        ButtonType GetButtonType() { return eType; }

        void Activate();
};

#endif