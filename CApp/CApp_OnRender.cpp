#include "CApp.h"

void CApp::OnRender() 
{
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);

	CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

    // Objects
    for(int i = 0;i < CObjectMenager::ObjectList.size();i++) 
    {
        if(!CObjectMenager::ObjectList[i]) continue;

        CObjectMenager::ObjectList[i]->OnRender(Surf_Display);
    }

    // Units
    for(int i = 0;i < CUnitMenager::UnitList.size();i++) 
    {
        if(!CUnitMenager::UnitList[i]) continue;

        CUnitMenager::UnitList[i]->OnRender(Surf_Display);
    }

	for(int i = 0; i < MAX_INTERFACEOBJECTS; i++) 
    {   
        if(!CInterfaceMenager::InterfaceMenager.InterfaceList[i]) continue;
                
        CInterfaceMenager::InterfaceMenager.InterfaceList[i]->OnRender(Surf_Display);
    }

    //OurHandledButton
    if(pSelectedButton)
        pSelectedButton->OnRender(Surf_Display);

	SDL_Flip(Surf_Display);
}

