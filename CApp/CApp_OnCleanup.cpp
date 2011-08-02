#include "CApp.h"

void CApp::OnCleanup() 
{
	CArea::AreaControl.OnCleanup();

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

    // Interface
	for(int i = 0;i < MAX_INTERFACEOBJECTS;i++) 
    {
        if(!CInterface::InterfaceControl.Interface[i]) continue;

        CInterface::InterfaceControl.Interface[i]->OnCleanup();
        CInterface::InterfaceControl.Interface[i] = NULL;
    }

    CObject::ObjectList.clear();
    CEntity::EntityList.clear();

    SDL_FreeSurface(Surf_Display);
    TTF_Quit();
    SDL_Quit();
}
