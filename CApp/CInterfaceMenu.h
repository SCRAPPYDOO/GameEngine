#ifndef _CINTERFACEMENU_H_
    #define _CINTERFACEMENU_H_

#include "CInterface.h"

enum
{
	INTERFACE_MENU_MAXCHARSLOTS = 6,

};

enum 
{
	CHAR_NAME,
	CHAR_RACE,
	CHAR_LEVEL,
	CHAR_CLASS,
	CHAR_MAX_SURF,
};

class CInterfaceMenu : public CInterface
{
    public:
        CInterfaceMenu();
        ~CInterfaceMenu() {}

    public: //Virtual
        bool OnLoad();
        void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
		void OnButtonActivate(ButtonType Type);

		bool LoadCharacters();

	private:
		int SelectedChar;
		SDL_Surface* SelectedCharSurf;
		SDL_Surface* Surf[INTERFACE_MENU_MAXCHARSLOTS][CHAR_MAX_SURF];
		//List Of Sharacters
};

#endif