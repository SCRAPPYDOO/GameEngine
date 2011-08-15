#include "CInterfaceCharacterCreator.h"
#include "CInterfaceMenager.h"

#define INTERFACE_CHARACTERCREATOR_W 1280
#define INTERFACE_CHARACTERCREATOR_H 720

CInterfaceCharacterCreator::CInterfaceCharacterCreator()
{
	OldX = 0;
    OldY = 0;
	eInterfaceType = INTERFACE_CHARACTERCREATOR;

    nPosX = 0;
    nPosY = 0;
    nWidht = INTERFACE_CHARACTERCREATOR_W;
    nHeight = INTERFACE_CHARACTERCREATOR_H;
}

bool CInterfaceCharacterCreator::OnLoad()
{
    if(CInterface::OnLoad() == false)
        return false;

    ButtonType eType;

    for(int i=0; i<2; ++i)
    {
        switch(i)
        {
            case 0: eType = BUTTON_CREATECHAR_NEXT; break;
            case 1: eType = BUTTON_CREATECHAR_BACK; break;
        }

        int x = nPosX + 5 + i * 33;
        int y = nPosY + 5;

		CButton *pButton = new CButton(x, y, eType);

        if(pButton->OnLoad() == false)
            break;
 
        ButtonsList.push_back(pButton);
    }

    return true;
}

void CInterfaceCharacterCreator::OnRender(SDL_Surface* Surf_Display)
{
	CInterface::OnRender(Surf_Display);
}

void CInterfaceCharacterCreator::OnCleanup()
{
    CInterface::OnCleanup();
}

void CInterfaceCharacterCreator::OnButtonActivate(ButtonType Type)
{
    switch(Type)
    {
        case BUTTON_CREATECHAR_NEXT:
        {
            //CleanUp();
            //LoadStep(++Step);
            break;
        }
        case BUTTON_CREATECHAR_BACK:
        {
            //CleanUp();
            //LoadStep(++Step);
            break;
        }
        case BUTTON_CREATECHAR_END:
        {
            //SaveChar();
            CInterfaceMenager::InterfaceMenager.CleanUpInterface(INTERFACE_CHARACTERCREATOR);
            CInterfaceMenager::InterfaceMenager.LoadInterface(INTERFACE_MAINMENU);
            break;
        }
        default: break;
    }
}

void CInterfaceCharacterCreator::NextStep()
{

}

void CInterfaceCharacterCreator::PreviousStep()
{

}

void CInterfaceCharacterCreator::End()
{

}