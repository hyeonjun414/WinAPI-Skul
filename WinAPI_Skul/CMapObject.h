#pragma once
#include "CObject.h"
class CMapObject :
    public CObject
{
public:
    CMapObject();
    CMapObject(OBJ_TYPE _eType);
    ~CMapObject();
};

