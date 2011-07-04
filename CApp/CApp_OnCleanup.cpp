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

    for(int i = 0;i < CInterface::InterfaceObjectList.size();i++) 
    {
        if(!CInterface::InterfaceObjectList[i]) continue;

        CInterface::InterfaceObjectList[i]->OnCleanup();
    }

    for(int i = 0;i < CButton::ButtonList.size();i++) 
    {
        if(!CButton::ButtonList[i]) continue;

        CButton::ButtonList[i]->OnCleanup();
    }

    CObject::ObjectList.clear();
    CEntity::EntityList.clear();
    CInterface::InterfaceObjectList.clear();
    CButton::ButtonList.clear();

    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}
