#ifndef _CUNITMENAGER_H_
    #define _CUNITMENAGER_H_

#include "CUnit.h"
#include <vector>

class CUnitMenager
{
    public:
        CUnitMenager();
        ~CUnitMenager() {}

        static std::vector <CUnit*> UnitList;

        static CUnit* GetUnit(int x, int y);
};

#endif