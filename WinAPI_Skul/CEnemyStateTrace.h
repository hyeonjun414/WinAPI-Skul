#pragma once
#include "CEnemyState.h"
class CEnemyStateTrace :
    public CEnemyState
{
public:
    virtual ~CEnemyStateTrace() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void    Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

};

