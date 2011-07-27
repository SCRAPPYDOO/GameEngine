#ifndef _CInterfaceA_H_
    #define _CInterfaceA_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

/*
    Main Menu
    Character Panel
    In GameMenu

    Button Panel


    Character Creator
    Main->character creator
*/

class CInterfaceA : public CInterface
{
    public:
        CInterfaceA();
        CInterfaceA(InterfaceType eType);
        ~CInterfaceA() {}

    protected:
        std::vector<CButton*>     ButtonsList;

    public:
        //void OnEvent
            void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void UpdateButtonsPosition();
        void LoadButtons();

        CButton* GetButton(int nPosX, int nPosY) const;
        void DeleteButtonFromSlot(CButton* pButton);
        bool AddButtonToSlot(CButton* pButton, int mX, int mY);
};

#endif