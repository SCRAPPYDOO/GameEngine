#ifndef _CINTERFACECHARACTERCREATOR_H_
	#define _CINTERFACECHARACTERCREATOR_H_

#include "CInterface.h"

class CInterfaceCharacterCreator : public CInterface
{
    public:
        CInterfaceCharacterCreator();
        ~CInterfaceCharacterCreator() {}

    public: //Virtual
        bool OnLoad();
		void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
};

#endif