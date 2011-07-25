#ifndef _CINTERFACEB_H_
    #define _CINTERFACEB_H_

#include "CSurface.h"
#include "CApp.h"
#include "CInterfaceA.h"
#include "CItem.h"

/*
    INTERFACE_BAG
    Show Items of selected Unit

    Bag->Equipment
    Equipment->Bag
    Bag->ButtonPanel
*/

#define BAG_MAX_SLOTS   4
#define BAG_MAX_X       8
#define BAG_MAX_Y       8

//#define INTERFACE_BAG_W 577
//#define INTERFACE_BAG_H 598

#define INTERFACE_EQUIPMENT_W 577
#define INTERFACE_EQUIPMENT_H 598

enum BAGSLOT
{
    BAG_ONE,
    BAG_TWO,
    BAG_THREE,
    BAG_FOUR,
};

class CInterfaceBag : public CInterfaceA
{
    public:
        CInterfaceBag();
        ~CInterfaceBag() {}

    protected:
        BAGSLOT ActualBag;
        CButton* ItemList[MAX_BAG_SLOTS][8][8];  

    public:
        bool OnLoad();
        //void OnEvent();
            void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void UpdateButtonsPosition();
        void LoadButtons();

    public:
        BAGSLOT GetActualBagSlot() const { return ActualBag; }
        void SetACtualSlotBag(BAGSLOT Slot) { ActualBag = Slot; }

        void SwitchBag(BAGSLOT NewBag);
        void SaveBag(BAGSLOT);
        void CleanUpBag(BAGSLOT);
        void LoadBag(BAGSLOT);
        void UpdateBagSlotPosition(BAGSLOT);
};

#endif