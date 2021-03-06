#ifndef _CINTERFACECHARSHEET_H_
    #define _CINTERFACECHARSHEET_H_

#include "CInterface.h"
#include "CItem.h"

#define INTERFACE_CHARSHEET_MAX 10
 
class CInterfaceCharSheet : public CInterface
{
    public:
        CInterfaceCharSheet();
        ~CInterfaceCharSheet() {}

    private:
        //CEntity* pChar; //character with we show on character sheet
        SDL_Surface* TextSurface[INTERFACE_CHARSHEET_MAX];

    public:
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void CleanUpSurface();
        void UpdateInterface();

        bool AddButtonToSlot(CButton* pButton, int mX, int mY);
		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		CButton* GetButton(int nPosX, int nPosY) const;
		void DeleteButtonFromSlot(CButton* pButton);

};

#endif