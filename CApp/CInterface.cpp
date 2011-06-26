#include "CInterface.h"

CInterface CInterface::InterfaceControl;

//Interface Surface
SDL_Surface* CInterface::Surf_MenuButton = NULL;

CInterface::CInterface() {}

bool CInterface::OnLoad(GameState eGameState)
{
	this->eGameState = eGameState;

	if(LoadInterface(eGameState) == false)
		return false;

    return true;
}

bool CInterface::OnEvent(int x, int y)
{
    //sprawdz czy jestemy na  polu interfacu
    // jezlei nie return true;
    //sprawdz wszytkie buttony  interfacu czy sa  na  x y i wstaw  button do on loop
    return false;
}

void CInterface::OnRender(SDL_Surface* Surf_Display)
{
	if(Surf_BackGround == NULL || Surf_Display == NULL) return;

	CSurface::OnDraw(Surf_Display, Surf_BackGround, 0, 0); //render BackGround

	for(int i = 0;i < CButton::ButtonList.size();i++) 
	{
        if(!CButton::ButtonList[i]) continue;

		CButton::ButtonList[i]->OnRender(Surf_Display);	
	}
}

void CInterface::OnCleanup()
{
	if(Surf_BackGround) 
	{
		SDL_FreeSurface(Surf_BackGround);
	}

    if(Surf_MenuButton) 
	{
		SDL_FreeSurface(Surf_MenuButton);
	}

    Surf_MenuButton = NULL;
	Surf_BackGround = NULL;

    //for(int i = 0;i < CButton::ButtonList.size();i++) 
    //{
    //    if(!CButton::ButtonList[i]) continue;

    //    CButton::ButtonList[i]->OnCleanup();
    //}

	CButton::ButtonList.clear();
}

bool CInterface::LoadInterface(GameState eGameState)
{
	OnCleanup();

	this->eGameState = eGameState;

	if(LoadSurface() == false)
		return false;

	if(LoadButtons() == false)
		return false;

	return true;
}

bool CInterface::LoadSurface()
{
	if(eGameState == MAIN_MENU)
	{
		if((Surf_BackGround = CSurface::OnLoad("./menu/menu_background.png")) == NULL) 
		{
			return false;
		}

		if((Surf_MenuButton = CSurface::OnLoad("./menu/menu_buttons.png")) == NULL) 
		{
			return false;
		}  
	}

	return true;
}

bool CInterface::LoadButtons()
{
	ButtonType Type = BUTTON_DEFAULT;

	switch(eGameState)
	{
		case MAIN_MENU:
		{
			for(int i=0; i<2; ++i)
			{
				CButton *Button = new CButton();

				switch(i)
				{
					case 0: Type = BUTTON_PLAY; break;
					case 1: Type = BUTTON_QUIT; break;
				}
					
				if(Button->OnLoad(Type) == false)
                    return false;

				CButton::ButtonList.push_back(Button);
			}

			break;
		}
	}

	return true;
}


