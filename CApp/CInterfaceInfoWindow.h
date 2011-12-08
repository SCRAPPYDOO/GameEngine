#ifndef _CINTERFACEINFOWINDOW_H_
    #define _CINTERFACEINFOWINDOW_H_

#include "CInterface.h"

class CInterfaceInfoWindow : public CInterface
{
    public:
        CInterfaceInfoWindow();
        ~CInterfaceInfoWindow() {}

    private:
		CUnit* pUnit;
		std::vector <SDL_Surface*> SurfaceTable;

		//static CInterfaceInfoWindow InfoWindow;

    public:
        bool OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

		void OnLoopCleanUp();
		void CleanUpPointers();

		void AddUnitPointer(CUnit* Unit) { SetUnit(Unit); }
		void SetUnit(CUnit* Unit);
};

#endif