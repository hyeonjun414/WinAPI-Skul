#pragma once
#include "CEnemyState.h"
class CEnemyStateAttack :
    public CEnemyState
{
private:
    int m_iAttackType;
public:

    virtual ~CEnemyStateAttack() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

