#include "CInterfaceMenu.h"

CInterfaceMenu::CInterfaceMenu()
{
	OldX = 0;
    OldY = 0;
	eInterfaceType = INTERFACE_MAINMENU;

	SelectedCharSurf = NULL;
	for(int i=0; i<INTERFACE_MENU_MAXCHARSLOTS; ++i)
	{
		for(int x=0; x<CHAR_MAX_SURF; ++x)
		{
			Surf[i][x] = NULL;
		}

		Character[i] = NULL;
	}
}

bool CInterfaceMenu::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

	for(int i=0; i<INTERFACE_MENU_MAXCHARSLOTS; ++i)
	{
		ButtonType eType;

		switch(i)
		{
			case 0: eType = BUTTON_MENU_SLOT_ONE; break;
			case 1: eType = BUTTON_MENU_SLOT_TWO; break;
			case 2: eType = BUTTON_MENU_SLOT_THREE; break;
			case 3: eType = BUTTON_MENU_SLOT_FOUR; break;
			case 4: eType = BUTTON_MENU_SLOT_FIVE; break;
			case 5: eType = BUTTON_MENU_SLOT_SIX; break;
			default: break;
		}

		CButton *pButton = new CButton(190, 60 + i * 40, eType);

		if(pButton->OnLoad() == false)
			continue;
 
		ButtonsList.push_back(pButton);
	}

	LoadCharacters();

    return true;
}

void CInterfaceMenu::OnLoop()
{
    CInterface::OnLoop();

	if(SelectedCharSurf) 
		SDL_FreeSurface(SelectedCharSurf);
	SelectedCharSurf = NULL;

	SelectedCharSurf = CSurface::RenderText(SelectedChar);
}

void CInterfaceMenu::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);

	for(int i=0; i<INTERFACE_MENU_MAXCHARSLOTS; ++i)
	{
		for(int x=0; x<CHAR_MAX_SURF; ++x)
		{
			if(Surf[i][x] == NULL) continue;

			CSurface::OnDraw(Surf_Display, Surf[i][x], 200 + x * 60, 60 + i * 40);
		}
	}

	if(SelectedCharSurf)
		CSurface::OnDraw(Surf_Display, SelectedCharSurf, 500, 200);
}

void CInterfaceMenu::OnCleanup()
{
    CInterface::OnCleanup();

	for(int i=0; i<INTERFACE_MENU_MAXCHARSLOTS; ++i)
	{
		for(int x=0; x<CHAR_MAX_SURF; ++x)
		{
			if(Surf[i][x]) 
				SDL_FreeSurface(Surf[i][x]);
			Surf[i][x] = NULL;
		}

		Character[i] = NULL;
	}
}

void CInterfaceMenu::OnButtonActivate(ButtonType Type)
{
    switch(Type)
    {
		case BUTTON_MENU_SLOT_ONE: SelectedChar = 0; break;
		case BUTTON_MENU_SLOT_TWO: SelectedChar = 1; break;
		case BUTTON_MENU_SLOT_THREE: SelectedChar = 2; break;
		case BUTTON_MENU_SLOT_FOUR: SelectedChar = 3; break;
		case BUTTON_MENU_SLOT_FIVE: SelectedChar = 4; break;
		case BUTTON_MENU_SLOT_SIX: SelectedChar = 5; break;

        default: break;
    }
}

bool CInterfaceMenu::LoadCharacters()
{
	for(int i=0; i<INTERFACE_MENU_MAXCHARSLOTS; ++i)
	{
		if(i==3) continue;

		Character[i] = new CCharacter();
		//if(!ImportChar(i))
		//{
		//	delete Character[i];
		//	Character[i] = NULL;
		//	break;
		//}
		//now we ned to get and render all info from character
		for(int x=0; x<CHAR_MAX_SURF; ++x)
		{
			switch(x)
			{
				case 0: Surf[i][x] = CSurface::RenderText("Malavon"); break;
				case 1:	Surf[i][x] = CSurface::RenderText("Elf"); break;
				case 2:	Surf[i][x] = CSurface::RenderText("Level 1"); break;
				case 3:	Surf[i][x] = CSurface::RenderText("Wizard"); break;
				//case 4:	Surf[i][x] = CSurface::RenderText("Marcin"); break;
				default: break;
			}
		}
	}

	return true;
}