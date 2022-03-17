#pragma once
#include "CState.h"
class CStateJumpAttack :
    public CState
{
private:
    float m_fJumpAttackLimitTime;
    float m_fJumpAttackCurTime;
public:
    CStateJumpAttack() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void    Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

};

