#ifndef _CINTERFACEMASSAGE_H_
    #define _CINTERFACEMASSAGE_H_

enum MassageType
{
    MASSAGE_TYPE_ERROR,
    MASSAGE_TYPE_EXPERIENCE,
};

struct Massage
{


};

class CInterfaceMassageHandler
{
    public:
        CInterfaceMassageHandler()
        {


        }
        ~CInterfaceMassageHandler() {}

        bool OnLoad() {}
        void OnRender(SDL_Surface* Surf_Display) {}
        void OnCleanup() {}

	public:	
};

#endif