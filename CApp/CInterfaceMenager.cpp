#include "CInterfaceMenager.h"

#include "CInterfaceUnit.h"
#include "CInterfaceEquip.h"
#include "CInterfaceMsgWindow.h"
#include "CInterfaceCharSheet.h"
#include "CInterfaceMenu.h"
#include "CInterfaceCharacterCreator.h"
#include "CInterfaceLoot.h"
#include "CInterfaceInfoWindow.h"

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

            for(int i=0; i<4; ++i)
            {
                switch(i)
                {
                    case 0: eType = INTERFACE_PLAYERINFO; break;                
                    case 1: eType = INTERFACE_CHARACTERPANEL; break;
                    case 2: eType = INTERFACE_MASAGEWINDOW; break;
					case 3: eType = INTERFACE_INFOWINDOW; break;
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
        case INTERFACE_GAMEMENU: pInterface = new CInterface(eType); break;
        case INTERFACE_CHARACTERPANEL: pInterface = new CInterface(eType); break;
        case INTERFACE_EQUIP: pInterface = new CInterfaceEquip(); break;
        case INTERFACE_LOOT: pInterface = new CInterfaceLoot(); break;
        case INTERFACE_SPELLBOOK: pInterface = new CInterface(eType); break;
        case INTERFACE_MASAGEWINDOW: pInterface = new CInterfaceMsgWindow(); break;
        case INTERFACE_CHARACTERSHEET: pInterface = new CInterfaceCharSheet(); break;
        case INTERFACE_CHARACTERCREATOR: pInterface = new CInterfaceCharacterCreator(); break;
		case INTERFACE_INFOWINDOW: pInterface = new CInterfaceInfoWindow(); break;

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

void CInterfaceMenager::MoveInterfaceToTop(CInterface* pInterface)
{
	//for(int it=0; it<InterfaceList.size(); ++it)
	//{
	//	if(InterfaceList[it] == NULL) continue;

	//	if(InterfaceList[it] == pInterface)
	//	{
	//		//InterfaceList.erase(InterfaceList[it]);
	//		InterfaceList.insert(InterfaceList.begin(), pInterface);
	//		
	//	}
	//}
};