#ifndef _CINTERFACEMENAGER_H_
    #define _CINTERFACEMENAGER_H_

#include "CInterface.h"

class CInterfaceMenager
{
    public:
        CInterfaceMenager();
        ~CInterfaceMenager() {}

        static CInterfaceMenager InterfaceMenager;
        CInterface*              InterfaceList[MAX_INTERFACEOBJECTS];

	public:	
		bool LoadInterface();
        bool LoadInterface(InterfaceType eType);
        void CleanUpInterface();
        void CleanUpInterface(InterfaceType eType);
        CInterface* GetInterface(int nPosX, int nPosY);
};

#endif