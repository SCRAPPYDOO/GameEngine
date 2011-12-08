#include "CInterfaceInfoWindow.h"

//CInterfaceInfoWindow CInterfaceInfoWindow::InfoWindow;

CInterfaceInfoWindow::CInterfaceInfoWindow()
{
	pUnit = NULL;

    eInterfaceType = INTERFACE_INFOWINDOW;

    for(int i = 0;i < SurfaceTable.size(); i++) 
    {   
        SurfaceTable[i] = NULL;
    }
}

bool CInterfaceInfoWindow::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    return true;
}

void CInterfaceInfoWindow::OnLoop()
{
	CInterface::OnLoop();
	OnLoopCleanUp();

	//Mysz musi wyslac info ze  wskaznik jest na Unit
	if(pUnit)
	{
		std::string name = pUnit->GetName();
		SDL_Surface* tempsurf = NULL;
		tempsurf =  CSurface::RenderText(name);

		SurfaceTable.push_back(tempsurf);
	}

	//if(pItem)
	//{
	//	zmien polozenie okna blizej itemu
	//}
	//skill
}

void CInterfaceInfoWindow::OnRender(SDL_Surface* Surf_Display)
{
	//CInterface::OnRender(Surf_Display);

	for(int i = 0; i < SurfaceTable.size(); ++i) 
	{  
		if(!SurfaceTable[i]) continue;

		CSurface::OnDraw(Surf_Display, SurfaceTable[i], nPosX, nPosY + i * 10 + 40); 
	}   
} 

void CInterfaceInfoWindow::OnCleanup()
{
	CInterface::OnCleanup();
	OnLoopCleanUp();
}

void CInterfaceInfoWindow::OnLoopCleanUp()
{
	for(int i = 0; i < SurfaceTable.size(); ++i) 
	{  
		if(SurfaceTable[i]) 
			SDL_FreeSurface(SurfaceTable[i]);

		SurfaceTable[i] = NULL;
	}  

	SurfaceTable.clear();
}

void CInterfaceInfoWindow::CleanUpPointers()
{
	pUnit = NULL;

}

void CInterfaceInfoWindow::SetUnit(CUnit* Unit)
{
	pUnit = Unit;
}