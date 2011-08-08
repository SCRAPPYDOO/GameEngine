#ifndef _COBJECTMENAGER_H_
    #define _COBJECTMENAGER_H_

#include "CObject.h"

class CObjectMenager
{
    public:
        CObjectMenager();
        ~CObjectMenager() {}

        static CObjectMenager ObjectMenager;

        static std::vector <CObject*> ObjectList;
};

#endif