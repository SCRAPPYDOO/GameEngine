#include "CApp.h"

void CApp::OnCleanup() 
{
	CArea::AreaControl.OnCleanup();

    CInterface::InterfaceControl.OnCleanup();

    // Entities
    for(int i = 0;i < CEntity::EntityList.size();i++) 
    {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnCleanup();
    }

    // Objects
    for(int i = 0;i < CObject::ObjectList.size();i++) 
    {
        if(!CObject::ObjectList[i]) continue;

        CObject::ObjectList[i]->OnCleanup();
    }

    CObject::ObjectList.clear();
    CEntity::EntityList.clear();

    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}
