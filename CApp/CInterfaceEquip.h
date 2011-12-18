#ifndef _CINTERFACEEQUIP_H_
    #define _CINTERFACEEQUIP_H_

#include "CInterface.h"
#include "CItem.h"

#define SLOT_W_H		45
#define DISTANSE_SLOT_TO_SLOT 5

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

    public: 
        bool AddButtonToSlot(CButton* pButton, int mX, int mY);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		CButton* GetButton(int nPosX, int nPosY) const;
		void DeleteButtonFromSlot(CButton* pButton);

};

#endif