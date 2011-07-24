#include "CButton.h"
#include "CInterfaceB.h"

CButton CButton::ButtonControl;
std::vector<CButton*> CButton::ButtonList;

CButton::CButton()
{
	x = 0;
	y = 0;
	w = 30;
	h = 30;

    pButtonSurface = NULL;

	eType = BUTTON_DEFAULT;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

CButton::CButton(int nPosX, int nPosY, ButtonType Type)    //Used by button panel on create
{
	x = nPosX;
	y = nPosY;
	w = 30;
	h = 30;

    pButtonSurface = NULL;

	eType = Type;
    eButtonState = BUTTONSTATE_UNSELECTED;
    eAnimationState = BUTTON_ANIME_NORMAL;
}

CButton::CButton(int nPosX, int nPosY, ButtonType Type, SDL_Surface* pSurface)    //Used by button panel on create
{
	x = nPosX;
	y = nPosY;
	w = 30;
	h = 30;

    pButtonSurface = pSurface;

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
	nButtonFlag += BUTTONFLAG_NOTMOVED;

    //ToDo: Load variables from file
	switch(eType)
	{
		case BUTTON_PLAY:
		{
			this->x = 640;
			this->y = 300;
			this->w = 134;

			break;
		}

        case BUTTON_QUIT:
        {
			this->x = 640;
			this->y = 350;
			this->w = 134;

			break;
		}

        case BUTTON_MENU:
        {
            this->x = 1050;
			this->y = 16;
			this->w = 134;
            break;
        }

        case BUTTON_GAMEMENU_QUIT: x = 500; y = 350; w = 134; h = 30; break;
        case BUTTON_GAMEMENU_RETURN: x = 500; y = 400; w = 134; h = 30; break;

        case BUTTON_CHARPANEL_CHARSHEET: x = 1003; y = 603; w = 30; h = 30; break;
        case BUTTON_CHARPANEL_EQUPMENT: x = 1036; y = 603; w = 30; h = 30; break;
        case BUTTON_CHARPANEL_SPELLBOOK: x = 1069; y = 603; w = 30; h = 30; break;
        case BUTTON_CHARPANEL_QUESTDIARY: x = 1105; y = 603; w = 30; h = 30; break;
        case BUTTON_CHARPANEL_GAMEMENU: x = 1149; y = 603; w = 30; h = 30; break;

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

        case BUTTON_MENU: //in game button menu
        {
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

		default: break;
	}
}

CButton* CButton::GetButton(int nX, int nY)
{
    CButton* pButton = NULL;

    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if(ButtonList[i]->IsButtonOnPos(nX,nY))
        {
            pButton = ButtonList[i];
            break;
        }
    }

    return pButton;
}

bool CButton::IsButtonOnPos(int mX, int mY)
{
    if( ( mX > x ) && ( mX < x + w) && ( mY > y ) && ( mY < y + h ) )
        return true;

    return false;
}

void CButton::OnDrop(int mX, int mY)
{
    //sprawdz czy zadne button panel nie ejst w pioblizu
    //for(int i = 0; i < CInterface::InterfaceObjectList.size(); i++) 
    //{   
    //    if(!CInterface::InterfaceObjectList[i]) continue;
    //            
    //    if(CInterface::InterfaceObjectList[i]->IsInterfaceOnPos(mX,mY))
    //       if(CInterface::InterfaceObjectList[i]->GetInterfaceType() == INTERFACE_BUTTON_PANEL)
    //            if(CInterface::InterfaceObjectList[i]->AddButtonToInterface(this, mX, mY))
    //                return;
    //}

    CButton::ButtonControl.DeleteButton(this);
}

void CButton::DeleteButton(CButton* pButton)
{
    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if(ButtonList[i] == pButton)
        {
            ButtonList[i]->OnCleanup();
            ButtonList[i] = NULL;
            break;
        }
    }
}

void CButton::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(Left)  //if we move something dont set animation
        return;

    //Set Proper Animation
    for(int i = 0;i < ButtonList.size();i++) 
    {   
        if(!ButtonList[i]) continue;
                
        if(ButtonList[i]->IsButtonOnPos(mX,mY))
        {
            ButtonList[i]->eAnimationState = BUTTON_ANIME_ONMOTION;
        }
        else
        {
            ButtonList[i]->eAnimationState = BUTTON_ANIME_NORMAL;
        }  
    }
}

