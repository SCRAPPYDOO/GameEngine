#ifndef _CINTERFACEMENU_H_
    #define _CINTERFACEMENU_H_

#include "CInterface.h"

enum
{
	INTERFACE_MENU_MAXCHARSLOTS = 6,

};

class CInterfaceMenu : public CInterface
{
    public:
        CInterfaceMenu();
        ~CInterfaceMenu() {}
		SDL_Surface * Surf_character;

    public: //Virtual
        bool OnLoad();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

		bool LoadCharacters();

	private:
		//List Of Sharacters
};

#endif