#include "CApp.h"

void CApp::OnCleanup() 
{
	CArea::AreaControl.OnCleanup();

    // Units
    for(int i = 0;i < CUnitMenager::UnitList.size();i++) 
    {
        if(!CUnitMenager::UnitList[i]) continue;

        CUnitMenager::UnitList[i]->OnCleanup();
    }

    // Objects
    for(int i = 0;i < CObjectMenager::ObjectList.size();i++) 
    {
        if(!CObjectMenager::ObjectList[i]) continue;

        CObjectMenager::ObjectList[i]->OnCleanup();
    }

    // Interface
	for(int i = 0;i < MAX_INTERFACEOBJECTS;i++) 
    {
        if(!CInterfaceMenager::InterfaceMenager.InterfaceList[i]) continue;

        CInterfaceMenager::InterfaceMenager.InterfaceList[i]->OnCleanup();
        CInterfaceMenager::InterfaceMenager.InterfaceList[i] = NULL;
    }

    CObjectMenager::ObjectList.clear();

    SDL_FreeSurface(Surf_Display);
    TTF_Quit();
    SDL_Quit();
}
