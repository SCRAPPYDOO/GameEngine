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

enum ButtonState
{
    BUTTONSTATE_UNSELECTED = 0,
    BUTTONSTATE_SELECTED   = 1,
    BUTTONSTATE_MOVED      = 2, 
};

class CButton
{
	public:
		CButton();
        CButton(int nValueX, int nValueY, ButtonType Type, SDL_Surface* pButtonSurface);

        ~CButton() {}

        static CButton ButtonControl;

		static std::vector<CButton*>    ButtonList;

    public:
        ButtonState eButtonState;

    protected:
        SDL_Surface* pButtonSurface;

		ButtonType eType;

		int x;
        int y;
        int w;
        int h;
        int nAnimationState;
        int nDistX, nDistY;

	public:
		bool OnLoad(ButtonType eType);

		void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

    public:
        void Activate();
        CButton* GetButton(int nX, int nY);

        virtual void OnMove(int nNextX, int nNextY) 
        { 
            x = nNextX - nDistX;
            y = nNextY - nDistY;
        }

        virtual void SetDistance(int nX, int nY) //Used for proper update movement for interface panels
        {
            nDistX = nX - x; 
            nDistY = nY - y;
        }

        int GetPosX() { return x; }
        int GetPosY() { return y; }
        int GetWidht() { return w; }
        int GetHeight() { return h; }

        void SetPositionX(int nValue) { x = nValue;}
        void SetPositionY(int nValue) { y = nValue;}

        ButtonType GetButtonType() { return eType; }

       
};

#endif