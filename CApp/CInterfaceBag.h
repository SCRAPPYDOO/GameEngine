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
 
    public: //Virtual
        bool OnLoad();
        void OnCleanup();

    public: //Own
        BAGSLOT GetActualBagSlot() const { return ActualBag; }
        void SetACtualSlotBag(BAGSLOT Slot) { ActualBag = Slot; }

        void SwitchBag(BAGSLOT NewBag);
        void SaveBag(BAGSLOT);
        void CleanUpBag(BAGSLOT);
        void LoadBag(BAGSLOT);
};

#endif