#ifndef _CCHARACTER_H_
    #define _CCHARACTER_H_

#include "CEntity.h"

class CCharacter /*: public CEntity */
{
    public:
        CCharacter() 
        {
            charName = "franek";
        }
        ~CCharacter() {}

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();

    protected:
        char* charName;

    public:
        char* GetName() const { return charName; }
};

#endif