#include "CInterfaceInfoWindow.h"
#include "CItem.h"
//CInterfaceInfoWindow CInterfaceInfoWindow::InfoWindow;

CInterfaceInfoWindow::CInterfaceInfoWindow()
{
	pUnit = NULL;
	pButton = NULL;

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

	if(CUnit* Unit = CUnitMenager::GetUnit(CMouse::Mouse.x, CMouse::Mouse.y))
	{
		pUnit = Unit;
	}
	else if(CInterface* pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(CMouse::Mouse.x, CMouse::Mouse.y))
	{
		//Add Interface Pointer

        if(CButton* Button = pInterface->GetButton(CMouse::Mouse.x, CMouse::Mouse.y))
        {
			pButton = Button;
		}
	}
	else
	{
		CleanUpPointers();
	}

	//Mysz musi wyslac info ze  wskaznik jest na Unit
	if(pUnit)
	{
		std::string name = pUnit->GetName();
		SDL_Surface* tempsurf = NULL;
		tempsurf =  CSurface::RenderText(name);

		SurfaceTable.push_back(tempsurf);
	}

	if(pButton)
	{
		switch(pButton->GetButtonClass())
		{
			case BUTTONCLASS_ITEM:
			{
				std::string name = ItemTable[pButton->GetID()].Name;
				SDL_Surface* tempsurf = NULL;
				tempsurf =  CSurface::RenderText(name);

				SurfaceTable.push_back(tempsurf);

			}

			default: break;

		}
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
	pButton = NULL;
}

void CInterfaceInfoWindow::SetUnit(CUnit* Unit)
{
	pUnit = Unit;
}

void CInterfaceInfoWindow::SetButton(CButton* Button)
{
	pButton = Button;
}
