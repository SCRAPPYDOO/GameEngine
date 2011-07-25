#ifndef _CInterfaceLoot_H_
    #define _CInterfaceLoot_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CApp.h"
#include "CInterfaceA.h"
#include "CItem.h"

/*
    Loot Window
*/

#define INTERFACE_LOOT_W_H 200

class CInterfaceLoot : public CInterfaceA
{
    public:
        CInterfaceLoot();
        ~CInterfaceLoot() {}

    protected:
        CItem* ItemList[4][4]; 

    public:
        bool OnLoad();
        void OnCleanup();

        void UpdateButtonsPosition();
        void LoadButtons();
};

#endif