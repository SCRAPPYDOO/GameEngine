#include "CApp.h"

bool CApp::OnInit() 
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) 
    {
        return false;
    }

    if( TTF_Init() == -1 )
    {
        return false;
    }

    CSurface::Font = TTF_OpenFont( "./font/times.ttf", 15 );
    if(CSurface::Font == NULL) return false;

    if(CInterfaceMenager::InterfaceMenager.LoadInterface() == false)
        return false;

	//DEBUG 
	//Created terst units

    //Test Character don delete this for now
	CUnit* unit = new CCharacter();
	unit->OnLoad();
	CUnitMenager::UnitList.push_back(unit);
	CPlayer::Player.pPlayerCharacter = unit;

	//Add Abilitys to abiltiys list
	int x=1;
	int y=1;
	ButtonType eType;
    for(int i=0; i<50; ++i)
    {
        switch(i)
        {

            case 0: eType = BUTTON_CHARPANEL_CHARSHEET; x = 1  ; y = 1; break;
            case 1: eType = BUTTON_CHARPANEL_CHARSHEET; x = 1    ; y = 1; break;
			case 2: eType = BUTTON_CHARPANEL_CHARSHEET; x = 1  ; y = 1; break;	
            default: break;
        }

        CButton *pButton = new CButton(x, y, eType);

        if(pButton->OnLoad() == false)
            break;

       unit->AbilityList.push_back(pButton);
    }

    for(int i=0; i<5; ++i)
    {
        switch(i)
        {

            case 0: eType = BUTTON_CHARPANEL_CHARSHEET; x = 1  ; y = 1; break;
            case 1: eType = BUTTON_CHARPANEL_CHARSHEET; x = 1    ; y = 1; break;
			case 2: eType = BUTTON_CHARPANEL_CHARSHEET; x = 1  ; y = 1; break;	
            default: break;
        }

        CButton *pButton = new CItem(1, 1, 1, 1);

		unit->ItemListTable[i][0] = pButton;

        if(pButton->OnLoad() == false)
            break;

       unit->AbilityList.push_back(pButton);
    }

    //Test Character don delete this for now
	//CUnit* punit = new CCharacter();
	//punit->OnLoad();
	//CUnitMenager::UnitList.push_back(punit);
    return true;
}

