#pragma once
#include "CEnemyState.h"
class CEnemyStateAttack :
    public CEnemyState
{
private:
    float   m_fAttackLimitTime;
    float   m_fAttackDelay;
    float   m_fFlowTime;
    int     m_iAttackCount;

    bool    m_bAttackInput;
    bool    m_bIsSecondAttack;
public:

    virtual ~CEnemyStateAttack() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

