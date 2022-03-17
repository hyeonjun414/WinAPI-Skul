#pragma once
#include "CState.h"
class CStateAttack :
    public CState
{
private:
    float   m_fAttackLimitTime;
    float   m_fAttackDelay;
    float   m_fFlowTime;
    int     m_iAttackCount;

    bool    m_bAttackInput;
    bool    m_bIsSecondAttack;
public:

    CStateAttack() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

