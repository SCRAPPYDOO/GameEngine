#ifndef _CINTERFACESKILLBOOK_H_
    #define _CINTERFACESKILLBOOK_H_

#include "CInterfaceMenager.h"

#define SLOT_W_H		30
#define DISTANSE_SLOT_TO_SLOT 5

#define MAX_SHOWED_SKILLS_IN_WINDOW 10

//#define INTERFACE_BAG_W 577
//#define INTERFACE_BAG_H 598

class CInterfaceSkill : public CInterface
{
    public:
        CInterfaceSkill();
        ~CInterfaceSkill() {}
 
	private:
		int ShowSkillFrom;
		int ShowSkillTo;

		//Name of ability showed
		SDL_Surface* AbilityName[10];

    public:
        bool OnLoad();
		void OnLoop();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

    public:
		void IncreaseMaxShowedLines() {}
		void DecreaseMaxShowedLines() {}
		void ScrollUp();
		void ScrollDown();

		void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
		CButton* GetButton(int nPosX, int nPosY) const;

		void AddButtonToSlot(CButton* pButton) {}
		bool AddButtonToSlot(CButton* pButton, int mX, int mY) { return false; }
		void DeleteButtonFromSlot(CButton* pButton) {}

		void OnButtonActivate(ButtonType Type); // called when button activate
		void OnButtonActivate(int Type) {}

		void CleanUpAbilityName();
		void RenderAbilityName();
};

#endif