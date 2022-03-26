#pragma once
#include "CState.h"
class CEnemyState :
    public CState
{
public:
    virtual ~CEnemyState() {}
    virtual CState* HandleInput(CObject* _pObj) { return nullptr; }
    virtual void    Update(CObject* _pObj) {}

    virtual void    Enter(CObject* _pObj) {}
    virtual void    Exit(CObject* _pObj) {}
};

