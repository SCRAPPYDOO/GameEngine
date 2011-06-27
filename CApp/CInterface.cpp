#include "CInterface.h"

CInterface CInterface::InterfaceControl;

//Interface Surface
SDL_Surface* CInterface::Surf_MenuButton = NULL;

CInterface::CInterface() 
{
    ShowGameMenu = false;
}

bool CInterface::OnLoad()
{
    if(LoadSurface() == false)
		return false;

	if(LoadInterface() == false)
		return false;

    return true;
}

    //sprawdz czy jestemy na  polu interfacu
    // jezlei nie return true;
    //sprawdz wszytkie buttony  interfacu czy sa  na  x y i wstaw  button do on loop

bool CInterface::OnEvent(int x, int y)
{
    for(int i = 0;i < CButton::ButtonList.size();i++) 
	{
        if(!CButton::ButtonList[i]) continue;

		if( ( x > CButton::ButtonList[i]->GetPosX() ) && ( x < CButton::ButtonList[i]->GetPosX() + CButton::ButtonList[i]->GetPosW()) && ( y > CButton::ButtonList[i]->GetPosY() ) && ( y < CButton::ButtonList[i]->GetPosY() + CButton::ButtonList[i]->GetPosH() ) )
        {
            CButton::ButtonList[i]->Activate();
            return true;
        }
    }

    return false;
}

void CInterface::OnRender(SDL_Surface* Surf_Display)
{
	if(Surf_BackGround == NULL || Surf_Display == NULL) return;

    switch(CApp::eGameState)
    {
        case MAIN_MENU:
        {
	        CSurface::OnDraw(Surf_Display, Surf_BackGround, 0, 0); //render BackGround
        }

        case TEST:
        {
            if(ShowGameMenu)
	            CSurface::OnDraw(Surf_Display, Surf_GameMenuBackGround, 500, 100); //render BackGround
        }

        default: break;
    }

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

    //Not Used 4 Now
    //for(int i = 0;i < CButton::ButtonList.size();i++) 
    //{
    //    if(!CButton::ButtonList[i]) continue;

    //    CButton::ButtonList[i]->OnCleanup();
    //}

	CButton::ButtonList.clear();
}

bool CInterface::LoadInterface()
{
	if(LoadButtons() == false)
		return false;

	return true;
}

bool CInterface::LoadSurface()
{
    if((Surf_BackGround = CSurface::OnLoad("./menu/menu_background.png")) == NULL) 
	{
	    return false;
	}

	if((Surf_MenuButton = CSurface::OnLoad("./menu/menu_buttons.png")) == NULL) 
	{
	    return false;
	}  

    if((Surf_GameMenuBackGround = CSurface::OnLoad("./menu/menu_gamebackground.png")) == NULL) 
	{
	    return false;
	}  

	return true;
}

bool CInterface::LoadButtons()
{
    CButton::ButtonList.clear();

	ButtonType Type;

	switch(CApp::eGameState)
	{
		case MAIN_MENU:
		{
			for(int i=0; i<MAX_MENU_BUTTONS; ++i)
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

        case TEST:
        {








            break;
        }

        case GAME_MENU:
        {

            break;
        }

        default: break;
	}

	return true;
}


