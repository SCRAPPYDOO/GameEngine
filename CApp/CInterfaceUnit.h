#ifndef _CUNITINFOPANEL_H_
    #define _CUNITINFOPANEL_H_

#include "CInterface.h"

enum InterfaceUnitDefines
{
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

    public:
        void UpdateHealth();
        void UpdateUnit();

        void CleanUpHealthBar();


};
#endif

