#ifndef _CUNITMENAGER_H_
    #define _CUNITMENAGER_H_

#include "CCharacter.h"

class CUnitMenager
{
    public:
        CUnitMenager();
        ~CUnitMenager() {}

        static std::vector <CUnit*> UnitList;

        static CUnit* GetUnit(int x, int y);
};

#endif