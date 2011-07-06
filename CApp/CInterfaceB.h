#ifndef _CINTERFACEB_H_
    #define _CINTERFACEB_H_

#include "CSurface.h"
#include "CApp.h"
#include "CInterfaceA.h"
#include "CItem.h"

/*
    INTERFACE_BAG
    INTERFACE_EQUIPMENT
*/

#define BAG_MAX_SLOTS   4
#define BAG_MAX_X       8
#define BAG_MAX_Y       8

#define INTERFACE_BAG_W 577
#define INTERFACE_BAG_H 598
#define INTERFACE_EQUIPMENT_W 577
#define INTERFACE_EQUIPMENT_H 598

class CInterfaceB : public CInterfaceA
{
    public:
        CInterfaceB();
        CInterfaceB(InterfaceType eType);
        ~CInterfaceB() {}

    protected:
        CItem* ItemList[MAX_BAG_SLOTS][8][8];  

    public:
        bool OnLoad();
        void OnCleanup();

        void UpdateButtonsPosition();
        void LoadButtons();
};

#endif