#ifndef _CINTERFACEEQUIP_H_
    #define _CINTERFACEEQUIP_H_

#include "CInterface.h"
#include "CItem.h"

/*
    INTERFACE_BAG
    Show Items of selected Unit

    Bag->Equipment
    Equipment->Bag
    Bag->ButtonPanel
*/

#define BAG_MAX_X       8
#define BAG_MAX_Y       8
#define SLOT_W_H		30

//#define INTERFACE_BAG_W 577
//#define INTERFACE_BAG_H 598

class CInterfaceEquip : public CInterface
{
    public:
        CInterfaceEquip();
        ~CInterfaceEquip() {}
 
    public: //Virtual
        bool OnLoad();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

    public: //Own
        void SaveBag();
        void CleanUpBag();
        void LoadBag();

        bool AddButtonToSlot(CButton* pButton, int mX, int mY);

		CButton* AddItemToSlot(CButton* pButton, int mX, int mY);

	private:
		CButton* ItemSlot[BAG_MAX_X][BAG_MAX_Y];

};

#endif