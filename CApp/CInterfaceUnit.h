#ifndef _CUNITINFOPANEL_H_
    #define _CUNITINFOPANEL_H_

#include "CInterface.h"
#include "CButtonShortcut.h"
#include "CInterfaceMenager.h"

enum InterfaceUnitDefines
{
	SLOT_W_H = 30,
	SLOT_MAX_X = 8,
	SLOT_MAX_Y = 2,
    HEALTHBARRANGE = 100,
    HEALTHBARHEIGHT = 20,
};

class CInterfaceUnit : public CInterface
{
    public:
        CInterfaceUnit();
        CInterfaceUnit(InterfaceType eType);
        ~CInterfaceUnit() {}

    public:
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

    private:
        CUnit* pUnit;
        int nHealth;
        int nMaxHealth;
        int nHealthBarRange;
        SDL_Surface* Surf_UnitStatus;
        SDL_Surface* Surf_UnitImage;
        SDL_Surface* Surf_UnitName;
        SDL_Surface* Surf_Percentage;

		CUnit* pTarget;
        int nTargetHealth;
        int nTargetMaxHealth;
        int nTargetHealthBarRange; //health bar
        SDL_Surface* Surf_TargetUnitImage;
        SDL_Surface* Surf_TargetUnitName;
        SDL_Surface* Surf_TargetHealthPercText;

	public:

		bool AddButtonToSlot(CButton* pButton, int mX, int mY);

	//Units Info
    public:
        void UpdateHealth();
        void UpdateUnit();

		void UpdateTarget();

		void CleanUpPlayerSurf();
		void CleanUpTargetSurf();

        void CleanUpHealthBar();


};
#endif

