#include "CInterfaceMenager.h"

#include "CInterfaceUnit.h"
#include "CInterfaceEquip.h"
#include "CInterfaceMsgWindow.h"
#include "CInterfaceCharSheet.h"
#include "CInterfaceMenu.h"
#include "CInterfaceCharacterCreator.h"

CInterfaceMenager CInterfaceMenager::InterfaceMenager;

CInterfaceMenager::CInterfaceMenager()
{
	for(int i=0; i<MAX_INTERFACEOBJECTS; ++i)
	{
		InterfaceList[i] = NULL;
	}
}

bool CInterfaceMenager::LoadInterface()
{
    CleanUpInterface();

    switch(CApp::eGameState)
    {
        case MAIN_MENU:
        {
            if(LoadInterface(INTERFACE_MAINMENU) == false)
                return false;

            break;
        }

        case TEST:
        {
            InterfaceType eType;

            for(int i=0; i<6; ++i)
            {
                switch(i)
                {
                    case 0: eType = INTERFACE_PLAYERINFO; break;      
                    case 1: eType = INTERFACE_BUTTON_PANEL; break;           
                    case 2: eType = INTERFACE_CHARACTERPANEL; break;
                    case 4: eType = INTERFACE_MASAGEWINDOW; break;
                    case 5: eType = INTERFACE_TARGET; break;
                    default: break;
                }

                if(LoadInterface(eType) == false)
                    return false;
            }

            break;
        }

        default: return false;
    }

	return true;
}

bool CInterfaceMenager::LoadInterface(InterfaceType eType)
{
    CInterface* pInterface = NULL;

    switch(eType)
    {
        case INTERFACE_MAINMENU: pInterface = new CInterfaceMenu(); break;
        case INTERFACE_PLAYERINFO: pInterface = new CInterfaceUnit(); break;
        case INTERFACE_BUTTON_PANEL: pInterface = new CInterface(eType); break;
        case INTERFACE_GAMEMENU: pInterface = new CInterface(eType); break;
        case INTERFACE_CHARACTERPANEL: pInterface = new CInterface(eType); break;
        case INTERFACE_EQUIP: pInterface = new CInterfaceEquip(); break;
        case INTERFACE_LOOT: pInterface = new CInterface(eType); break;
        case INTERFACE_SPELLBOOK: pInterface = new CInterface(eType); break;
        case INTERFACE_MASAGEWINDOW: pInterface = new CInterfaceMsgWindow(); break;
        case INTERFACE_CHARACTERSHEET: pInterface = new CInterfaceCharSheet(); break;
        case INTERFACE_TARGET: pInterface = new CInterfaceUnit(eType); break;
        case INTERFACE_CHARACTERCREATOR: pInterface = new CInterfaceCharacterCreator(); break;
        default: return false;
    }

    if(pInterface && pInterface->OnLoad() == false)
        return false;

	InterfaceList[eType] = pInterface;

    return true;
}

void CInterfaceMenager::CleanUpInterface()
{
	for(int i = 0;i < MAX_INTERFACEOBJECTS;i++) 
    {
        if(!InterfaceList[i]) continue;

        InterfaceList[i]->OnCleanup();
		InterfaceList[i] = NULL;
    }
}

void CInterfaceMenager::CleanUpInterface(InterfaceType eType)
{	
	if(InterfaceList[eType] == NULL)
		return;

	InterfaceList[eType]->OnCleanup();
	InterfaceList[eType] = NULL; 
}

CInterface* CInterfaceMenager::GetInterface(int nPosX, int nPosY)
{
	for(int i = 0; i < MAX_INTERFACEOBJECTS; i++) 
    {   
        if(!InterfaceList[i]) continue;
                
        if( ( nPosX > InterfaceList[i]->GetPosX() ) && ( nPosX < InterfaceList[i]->GetPosX() + InterfaceList[i]->GetWidht()) && ( nPosY > InterfaceList[i]->GetPosY() ) && ( nPosY < InterfaceList[i]->GetPosY() + InterfaceList[i]->GetHeight() ) )
        {
            return InterfaceList[i];
        }
    }

    return NULL;
}