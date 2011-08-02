#ifndef _CINTERFACEB_H_
    #define _CINTERFACEB_H_

#include "CInterface.h"
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

enum BAGSLOT
{
    BAG_ONE,
    BAG_TWO,
    BAG_THREE,
    BAG_FOUR,
};

enum SlotType
{
    SLOT_DEFAULT,
    SLOT_BAG,

    SLOT_MAINHAND,
    SLOT_SECONDHAND,

    SLOT_HEAD,
    SLOT_HANDS,
    SLOT_CHEST,
    SLOT_BOOTS,
    SLOT_AMMO,
    SLOT_BELT,
    SLOT_NECK,
    SLOT_RING,
};

class CInterfaceEquip : public CInterface
{
    public:
        CInterfaceEquip();
        ~CInterfaceEquip() {}

    protected:
        BAGSLOT ActualBag;
 
    public: //Virtual
        bool OnLoad();
        void OnCleanup();

    public: //Own
        BAGSLOT GetActualBag() const { return ActualBag; }
        void SetActualBag(BAGSLOT Slot) { ActualBag = Slot; }

        void SwitchBag(BAGSLOT NewBag);
        void SaveBag();
        void CleanUpBag();
        void LoadBag(BAGSLOT);

        bool AddButtonToSlot(CButton* pButton, int mX, int mY);
};

#endif