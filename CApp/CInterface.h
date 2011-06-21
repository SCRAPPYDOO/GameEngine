#ifndef _CINTERFACE_H_
    #define _CINTERFACE_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"

class CButton 
{
	public:
		int x;
        int y;
        int w;
        int h;


};

class CInterface 
{
	public:
		SDL_Surface*			Surf_ButtonSet;
        SDL_Surface*            Surf_BackGround;

	private:
		std::vector<CButton*>      ButtonList;

	public:
        CInterface() {}
        ~CInterface() {}
    public:
        int x;
        int y;
        int w;
        int h;

	public:
        bool OnLoad(char* File) {}

        void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {}

};

#endif
