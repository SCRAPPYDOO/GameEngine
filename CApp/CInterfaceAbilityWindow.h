#ifndef _CINTERFACEABILITYWND_H_
    #define _CINTERFACEABILITYWND_H_

#include "CInterface.h"

struct Ability
{
	CButton* pAbilityButton;
	SDL_Surface* pAbilityNameSurf;
}

class CInterfaceAbilityWindow : public CInterface
{
    public:
        CInterfaceAbilityWindow();
        ~CInterfaceAbilityWindow() {}

    private:
		//Container with buttons
		std::vector <Ability> AbilityList;

    public:
        bool OnLoad();
        void OnLoop() {}
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

        void CleanUpSurface();
        void UpdateInterface();
};

#endif