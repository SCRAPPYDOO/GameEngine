#include "CButton.h"
#include "CInterfaceMenager.h"
#include "CApp.h"

CButton::CButton(int nPosX, int nPosY, ButtonType Type)    //Used by button panel on create
{
	x = nPosX;
	y = nPosY;
	w = 30;
	h = 30;
    nButtonFlag = 0;
    nPreviousX = x;
    nPreviousY = y;

    pButtonSurface = NULL;
    eButtonClass = BUTTONCLASS_BUTTON;
	eButtonType = Type;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

CButton::CButton(int nPosX, int nPosY, int Type)    //Used by button panel on create
{
	ButtonIndex = Type;

	x = nPosX;
	y = nPosY;
	w = 30;
	h = 30;
    nButtonFlag = 0;
    nPreviousX = x;
    nPreviousY = y;

    pButtonSurface = NULL;
    eButtonClass = BUTTONCLASS_BUTTON;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

bool CButton::OnLoad()
{
    if(OnLoad(eButtonType))
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

        case BUTTON_GAMEMENU_QUIT:
        case BUTTON_GAMEMENU_RETURN: w = 134; break;

        case BUTTON_CHARPANEL_CHARSHEET: break;
        case BUTTON_CHARPANEL_EQUIPMENT: break;
        case BUTTON_CHARPANEL_SPELLBOOK: break;
        case BUTTON_CHARPANEL_QUESTDIARY: break;
        case BUTTON_CHARPANEL_GAMEMENU: break;

        case BUTTON_EQUIPMENT_QUIT: break;

        case BUTTON_SWORD:
        {
            eButtonClass = BUTTONCLASS_ITEM;
            //nButtonFlag += BUTTONFLAG_LOOT;
            break;
        }
		default: break;
	}

    this->eButtonType = eType;

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
	if(ButtonIndex > HeroicFeatsBegin - 1 && ButtonIndex < HeroicFeatsEnd)
    {
        CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_CHARACTERCREATOR]->OnButtonActivate(ButtonIndex);
		return;
	}

    //eAnimationState = BUTTON_ANIME_ONCLICK;

    switch(eButtonType)
	{
		case BUTTON_MENU_DELETE_CHARACTER: 
		{
			//Delet Char(SelectedChar)
			break;
		}
		case BUTTON_MENU_ENTERTOWORLD: 
		{
			//CPlayer->LoadCharacter(SelectedCharacter);
			//ButtonPlay;

		}

        case BUTTON_MENU_CREATECHARACTER: //Go To Create Character Menu
        {
            CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_MAINMENU);
            CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_CHARACTERCREATOR);
            break;
        }

		case BUTTON_MENU_SLOT_ONE:
		case BUTTON_MENU_SLOT_TWO:
		case BUTTON_MENU_SLOT_THREE:
		case BUTTON_MENU_SLOT_FOUR:
		case BUTTON_MENU_SLOT_FIVE:
		case BUTTON_MENU_SLOT_SIX:
		{
			CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MAINMENU]->OnButtonActivate(eButtonType);
			break;
		}

		case BUTTON_PLAY:
		{
            CApp::eGameState = TEST;

            CInterfaceMenager::InterfaceMenager.LoadInterface();

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
            CInterfaceMenager::InterfaceMenager.LoadInterface();
            break;  
        }
        case BUTTON_GAMEMENU_RETURN: // ingame game menu button return
        {
			if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_GAMEMENU])
            {
                CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_GAMEMENU);
            }

            break;
        }
        //Other Button in Game Menu

		//Character Panel
        case BUTTON_CHARPANEL_CHARSHEET: 
        {
			if(!CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_CHARACTERSHEET])
			{
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Enter To Character Sheet");
				CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_CHARACTERSHEET);
			}
			else
				CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_CHARACTERSHEET);

            break;
        }
        case BUTTON_CHARPANEL_EQUIPMENT:
        {
            CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("equpment");
			if(!CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_EQUIP])
			{
				CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_EQUIP);
			}
			else
				CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_EQUIP);

            break;
        }
        case BUTTON_CHARPANEL_SPELLBOOK:
        {
			if(!CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_SPELLBOOK])
			{
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("Enter to SpellBook !!");
				CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_SPELLBOOK);
			}
			else
				CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_SPELLBOOK);

            break;
        }
        case BUTTON_CHARPANEL_QUESTDIARY: break;
        case BUTTON_CHARPANEL_GAMEMENU:
        {
			if(!CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_GAMEMENU])
			{
                CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_MASAGEWINDOW]->AddMsg("gamemenu");
				CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_GAMEMENU);
			}
			else
				CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_GAMEMENU);

            break;
        }

		//Equipment Buttons
        case BUTTON_EQUIPMENT_QUIT: 
		{
			if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_EQUIP])
            {
                CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_EQUIP);
            }

			break;
		}

        //Interface Loot buttons
        case BUTTON_LOOT_QUIT: 
        {
			if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_LOOT])
            {
                CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_LOOT);
            }
            break;
        }
        case BUTTON_LOOT_LOOTALL: break;

        //SpellBook
        case BUTTON_SPELLBOOK_QUIT:         
        {
			if(CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_SPELLBOOK])
            {
                CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_SPELLBOOK);
            }
            break;
        }

        //Chreate Character Buttons
        case BUTTON_CREATECHAR_NEXT:
        case BUTTON_CREATECHAR_BACK:
        case BUTTON_CREATECHAR_END:
		case BUTTON_CREATECHAR_DRAGONBORN:
		case BUTTON_CREATECHAR_DWARF:
		case BUTTON_CREATECHAR_ELADRIN:
		case BUTTON_CREATECHAR_ELF:
		case BUTTON_CREATECHAR_HALFELF:
		case BUTTON_CREATECHAR_HALFLING:
		case BUTTON_CREATECHAR_HUMAN:
		case BUTTON_CREATECHAR_TIEFLING:
		case BUTTON_CREATECHAR_CLERIC:
		case BUTTON_CREATECHAR_FIGHTER:
		case BUTTON_CREATECHAR_PALADIN:
		case BUTTON_CREATECHAR_RANGER:
		case BUTTON_CREATECHAR_ROGUE:
		case BUTTON_CREATECHAR_WARLOCK:
		case BUTTON_CREATECHAR_WARLORD:
		case BUTTON_CREATECHAR_WIZARD:
		case BUTTON_CREATECHAR_STR:
		case BUTTON_CREATECHAR_CON:
		case BUTTON_CREATECHAR_DEX:
		case BUTTON_CREATECHAR_INT:
		case BUTTON_CREATECHAR_WIS:
		case BUTTON_CREATECHAR_CHA:
		case BUTTON_CREATECHAR_INCREASE:
		case BUTTON_CREATECHAR_DECREASE:
		case BUTTON_CREATECHAR_SKILL_ACROBATICS:
		case BUTTON_CREATECHAR_SKILL_ARCANA:
		case BUTTON_CREATECHAR_SKILL_ATHLETICS:
		case BUTTON_CREATECHAR_SKILL_BLUFF:
		case BUTTON_CREATECHAR_SKILL_DIPLOMACY:
		case BUTTON_CREATECHAR_SKILL_DUNGEONEERING: 
		case BUTTON_CREATECHAR_SKILL_ENDURANCE:
		case BUTTON_CREATECHAR_SKILL_HEAL:
		case BUTTON_CREATECHAR_SKILL_HISTORY:
		case BUTTON_CREATECHAR_SKILL_INSIGHT:
		case BUTTON_CREATECHAR_SKILL_INTIMIDATE:
		case BUTTON_CREATECHAR_SKILL_NATURE:
		case BUTTON_CREATECHAR_SKILL_PERCEPTION:
		case BUTTON_CREATECHAR_SKILL_RELIGION:
		case BUTTON_CREATECHAR_SKILL_STEALTH:
		case BUTTON_CREATECHAR_SKILL_STREETWISE:
        {
            CInterfaceMenager::InterfaceMenager.InterfaceList[INTERFACE_CHARACTERCREATOR]->OnButtonActivate(eButtonType);
            break;
        }

        //test
        case BUTTON_SWORD:
        {

            break;
        }

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
    //if(eButtonClass != BUTTONCLASS_SHORTCURT)
    {
        //Check if we are on interface and try to add to him
        if(CInterface* pInterface = CInterfaceMenager::InterfaceMenager.GetInterface(mX, mY))
        {
            //if(CInterface* bInterface = CInterface::InterfaceControl.GetInterface(nPreviousX, nPreviousY))
            //{
            //    if(bInterface && bInterface->GetInterfaceType() != INTERFACE_LOOT && pInterface->GetInterfaceType() = INTERFACE_BUTTON_PANEL)
  
                    if(pInterface && pInterface->AddButtonToSlot(this, mX, mY))
                        return;
            //}
        }
        //If we are not droped on interface 
        else 
        {
            //spell and shortcut delete
            if(eButtonClass == BUTTONCLASS_SHORTCURT || eButtonClass == BUTTONCLASS_SPELL)
            {
                OnCleanup();
                return;
            }
            //item need to ask to destroy or not
        }

        //If we can go to new interface we return
        if(CInterface *pOldInterfaceSlot = CInterfaceMenager::InterfaceMenager.GetInterface(nPreviousX, nPreviousY))
        {
            if(pOldInterfaceSlot)
            {
                pOldInterfaceSlot->AddButtonToSlot(this);
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

