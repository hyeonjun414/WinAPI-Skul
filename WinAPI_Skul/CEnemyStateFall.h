#pragma once
#include "CEnemyState.h"
class CEnemyStateFall :
    public CEnemyState
{
private:
public:
    CEnemyStateFall() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);


};

