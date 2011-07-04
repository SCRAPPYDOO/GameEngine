#ifndef _CBUTTONPANEL_H_
    #define _CBUTTONPANEL_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterface.h"

#define MAX_BUTTON_SLOTS 10

class CButtonPanel : public CInterface
{
    public:
        CButtonPanel();

        ~CButtonPanel() {}

    private:
        SDL_Surface*              Surf_ButtonPanel;
        CButton*                  ButtonSlot[MAX_BUTTON_SLOTS];

    public:
        bool OnLoad();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void OnMove(int nNextX, int nNextY);
        void AddButton();
        bool AddButtonToInterface(CButton* pButton, int mX, int mY);
        void UpdateButtonsPosition();
        void DeleteMovedButtons();
};

#endif