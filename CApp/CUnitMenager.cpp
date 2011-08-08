#include "CUnitMenager.h"

std::vector<CUnit*> CUnitMenager::UnitList;

CUnitMenager::CUnitMenager()
{

}

CUnit* CUnitMenager::GetUnit(int x, int y)
{
    CUnit* temp = NULL;

    for(int i = 0;i < CUnitMenager::UnitList.size();i++) 
    {   
        if(!CUnitMenager::UnitList[i]) continue;

        //If the mouse is over the Entity
        if( ( x > CUnitMenager::UnitList[i]->GetAnimPosX() ) && ( x < CUnitMenager::UnitList[i]->GetAnimPosX() + CUnitMenager::UnitList[i]->GetWidht()) && ( y > CUnitMenager::UnitList[i]->GetAnimPosY() ) && ( y < CUnitMenager::UnitList[i]->GetAnimPosY() + CUnitMenager::UnitList[i]->GetHeight() ) )
        {  
            temp = CUnitMenager::UnitList[i];
            return temp;
        }
    }

    return temp;
}