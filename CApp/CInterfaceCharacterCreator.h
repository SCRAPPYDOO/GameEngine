#ifndef _CINTERFACECHARACTERCREATOR_H_
	#define _CINTERFACECHARACTERCREATOR_H_

#include "CInterface.h"

enum Steps
{
    STEP_RACE,
    STEP_CLASS,
    STEP_NAME,
};



class CInterfaceCharacterCreator : public CInterface
{
    public:
        CInterfaceCharacterCreator();
        ~CInterfaceCharacterCreator() {}

    public: //Virtual
        bool OnLoad();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void OnButtonActivate(ButtonType Type);
        void ShowInfo();
        void NextStep();
        void PreviousStep();
        void End();
};

#endif