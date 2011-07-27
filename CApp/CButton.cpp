#include "CButton.h"
#include "CInterfaceBag.h"

CButton::CButton(int nPosX, int nPosY, ButtonType Type)    //Used by button panel on create
{
	x = nPosX;
	y = nPosY;
	w = 30;
	h = 30;

    nPreviousX = x;
    nPreviousY = y;

    pButtonSurface = NULL;

    eButtonClass = BUTTONCLASS_BUTTON;
	eType = Type;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

bool CButton::OnLoad()
{
    if(OnLoad(eType))
        return true;

    return false;
}

bool CButton::OnLoad(ButtonType eType)
{
    char* Surf_Name = "./error/surf_error.png";

	//ALLL BUTTONS ARE NOW NOT MOVABLE
	//nButtonFlag += BUTTONFLAG_NOTMOVED;

    //ToDo: Load variables from file
	switch(eType)
	{
		case BUTTON_PLAY:
        case BUTTON_QUIT:
        case BUTTON_CREATECHARACTER:

        case BUTTON_GAMEMENU_QUIT:
        case BUTTON_GAMEMENU_RETURN: w = 134; break;

        case BUTTON_CHARPANEL_CHARSHEET: break;
        case BUTTON_CHARPANEL_EQUPMENT: break;
        case BUTTON_CHARPANEL_SPELLBOOK: break;
        case BUTTON_CHARPANEL_QUESTDIARY: break;
        case BUTTON_CHARPANEL_GAMEMENU: break;

        case BUTTON_BAG_SWITCHBAG: break;
        case BUTTON_BAG_QUIT: break;
        case BUTTON_BAG_SLOT_ONE: break;

		default: break;
	}

    this->eType = eType;

    if((pButtonSurface = CSurface::OnLoad(Surf_Name)) == false)
        return false;

    return true;
}

void CButton::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Display == NULL || pButtonSurface == NULL)
        return;
	
    CSurface::OnDraw(Surf_Display, pButtonSurface, x, y, w*eAnimationState, 0, w, h);
}

void CButton::OnCleanup()
{
    if(pButtonSurface != NULL)
		SDL_FreeSurface(pButtonSurface);

    pButtonSurface = NULL;
}

void CButton::Activate()
{
    //eAnimationState = BUTTON_ANIME_ONCLICK;

    switch(eType)
	{
		case BUTTON_PLAY:
		{
            CApp::eGameState = TEST;

            CInterface::InterfaceControl.LoadInterface();

            if(CArea::AreaControl.OnLoad("./maps/1.area") == false) 
                break;

			break;
		}

        case BUTTON_QUIT:
        {
            //CApp::GameControl.OnExit();
            break;
		}

		//In Game Menu buttons
        case BUTTON_GAMEMENU_QUIT: 
        {
            CApp::eGameState = MAIN_MENU;
            CInterface::InterfaceControl.LoadInterface();
            break;  
        }
        case BUTTON_GAMEMENU_RETURN: // ingame game menu button return
        {
			if(CInterface::InterfaceControl.Interface[INTERFACE_GAMEMENU])
            {
                CInterface::InterfaceControl.CleanUpInterface(INTERFACE_GAMEMENU);
            }

            break;
        }
        //Other Button in Game Menu
		//Character Mini Panel
        case BUTTON_CHARPANEL_CHARSHEET: break;
        case BUTTON_CHARPANEL_EQUPMENT:
        {
			if(!CInterface::InterfaceControl.Interface[INTERFACE_BAG])
			{
				CInterface::InterfaceControl.LoadInterface(INTERFACE_BAG);
			}
			else
				CInterface::InterfaceControl.CleanUpInterface(INTERFACE_BAG);

            break;
        }
        case BUTTON_CHARPANEL_SPELLBOOK: break;
        case BUTTON_CHARPANEL_QUESTDIARY: break;
        case BUTTON_CHARPANEL_GAMEMENU:
        {
			if(!CInterface::InterfaceControl.Interface[INTERFACE_GAMEMENU])
			{
				CInterface::InterfaceControl.LoadInterface(INTERFACE_GAMEMENU);
			}
			else
				CInterface::InterfaceControl.CleanUpInterface(INTERFACE_GAMEMENU);

            break;
        }
		//Bag Buttons
        case BUTTON_BAG_SWITCHBAG: break;
        case BUTTON_BAG_QUIT: 
		{
			if(CInterface::InterfaceControl.Interface[INTERFACE_BAG])
            {
                CInterface::InterfaceControl.CleanUpInterface(INTERFACE_BAG);
            }

			break;
		}
        case BUTTON_BAG_SLOT_ONE: /*CInterfaceB::BagControl.SwitchBag(BAG_ONE);*/ break;
        //Interface Loot buttons
        case BUTTON_LOOT_QUIT: 
        {
			if(CInterface::InterfaceControl.Interface[INTERFACE_LOOT])
            {
                CInterface::InterfaceControl.CleanUpInterface(INTERFACE_LOOT);
            }
            break;
        }
        case BUTTON_LOOT_LOOTALL: break;

		default: break;
	}
}

bool CButton::IsButtonOnPos(int mX, int mY)
{
    if( ( mX > x ) && ( mX < x + w) && ( mY > y ) && ( mY < y + h ) )
        return true;

    return false;
}

//ToDo: Need to add delete methods for dropen buttons
void CButton::OnDrop(int mX, int mY)
{
    //ToDo: Shortcut can only be moved from slot around ButtonInterface
    //Now Only deelted
    if(eButtonClass != BUTTONCLASS_SHORTCURT)
    {
        //Check if we are on interface and try to add to him
        if(CInterface* pInterface = CInterface::InterfaceControl.GetInterface(mX, mY))
        {
             if(pInterface && pInterface->AddButtonToSlot(this, mX, mY))
                 return;
        }

        //If we can go to new interface we return
        if(CInterface *pOldInterfaceSlot = CInterface::InterfaceControl.GetInterface(nPreviousX, nPreviousY))
        {
            if(pOldInterfaceSlot && pOldInterfaceSlot->AddButtonToSlot(this, nPreviousX, nPreviousY))
            {
                x = nPreviousX;
                y = nPreviousY;
                return;  
            }
        }
    }

    //If all patch are broken we delete our self
    OnCleanup();
}

void CButton::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    //If We hold Left button dont set animations
    if(Left)                                            
        return;

    if(IsButtonOnPos(mX, mY))
        eAnimationState = BUTTON_ANIME_ONMOTION;
    else
        eAnimationState = BUTTON_ANIME_NORMAL; 
}

