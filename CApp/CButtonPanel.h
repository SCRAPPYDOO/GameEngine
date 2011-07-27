#ifndef _CBUTTONPANEL_H_
    #define _CBUTTONPANEL_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterfaceA.h"

#define MAX_BUTTON_SLOTS 10

class CButtonPanel : public CInterfaceA
{
    public:
        CButtonPanel();
        ~CButtonPanel() {}

    private:


    public:
        bool OnLoad();
        void OnCleanup();

        bool AddButtonToSlot(CButton* pButton, int mX, int mY);
};

#endif