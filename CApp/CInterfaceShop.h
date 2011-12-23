#ifndef _CINTERFACESHOP_H_
    #define _CINTERFACESHOP_H_

#include "CInterface.h"

class CInterfaceShop : public CInterface
{
    public:
		CInterfaceShop();
		CInterfaceShop(int nID);
        ~CInterfaceShop() {}

	public:	
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

		void OnButtonActivate(ButtonType Type);

	private:

};

#endif

