#ifndef _CInterfaceA_H_
    #define _CInterfaceA_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

/*
    Main Menu
    Character Creator
    In GameMenu
    Character Panel

    Main->character creator
*/

class CInterfaceA : public CInterface
{
    public:
        CInterfaceA();
        CInterfaceA(InterfaceType eType);
        ~CInterfaceA() {}

    public:
        std::vector<CButton*>     ButtonsList;

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void UpdateButtonsPosition();
        void LoadButtons();
};

#endif