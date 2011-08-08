#include "CObject.h"

CObject::CObject() 
{
    Surf_Object = NULL;
}

CObject::~CObject() {}

bool CObject::OnLoad(char* File)
{
	if((Surf_Object = CSurface::OnLoad(File)) == NULL) 
    {
		return false;
	}

	CSurface::Transparent(Surf_Object, 255, 0, 255);

    return true;
}

void CObject::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Object == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Object, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY());
}

void CObject::OnCleanup()
{
    if(Surf_Object) 
    {
        SDL_FreeSurface(Surf_Object);
    }

    Surf_Object = NULL;
}
