#pragma once
#include "CEnemyState.h"

class CEnemyStateIdle :
    public CEnemyState
{
public:
    virtual ~CEnemyStateIdle() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void    Update(CObject* _pObj);

    virtual void    Enter(CObject* _pObj);
    virtual void    Exit(CObject* _pObj);

};

