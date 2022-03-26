#pragma once
#include "CEnemyState.h"
class CEnemyStateAppear :
    public CEnemyState
{
private:
    float m_fCurTime;
    float m_fDuration;

public:
    virtual ~CEnemyStateAppear() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

