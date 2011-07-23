#include "CApp.h"

void CApp::OnRender() 
{
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);

    switch(eGameState)
    {
        case TEST:
        {
	        CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

            // Objects
            for(int i = 0;i < CObject::ObjectList.size();i++) 
            {
                if(!CObject::ObjectList[i]) continue;

                CObject::ObjectList[i]->OnRender(Surf_Display);
            }

            for(int i = 0;i < CEntity::EntityList.size();i++) 
	        {
                if(!CEntity::EntityList[i]) continue;

                CEntity::EntityList[i]->OnRender(Surf_Display);
            } 
        }
    }

    for(int i = 0; i < CInterface::InterfaceObjectList.size(); i++) 
    {   
        if(!CInterface::InterfaceObjectList[i]) continue;
                
        CInterface::InterfaceObjectList[i]->OnRender(Surf_Display);
    }

	for(int i = 0; i < CInterface::InterfaceObjectList.size(); i++) 
    {   
        if(!CInterface::InterfaceObjectList[i]) continue;
                
        CInterface::InterfaceObjectList[i]->OnRender(Surf_Display);
    }

    for(int i = 0;i < CButton::ButtonList.size();i++) 
	{
            if(!CButton::ButtonList[i]) continue;

		    CButton::ButtonList[i]->OnRender(Surf_Display);	
	}

	SDL_Flip(Surf_Display);
}

