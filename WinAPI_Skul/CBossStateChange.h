#pragma once
#include "CBossState.h"

class CEnemyBoss;
class CBossStateChange :
    public CBossState
{
    Vec2 m_vOriginPos;
    float m_fNextAttackTime;
    float m_fNextAttackCurTime;
    float m_fMoveTime;
    float m_fCurTime;

    bool m_bOnceFunc;
    float m_fOnceFuncTime;
    float m_fOnceFuncCurTime;

    Vec2 m_vSweepVelocity;
    Vec2 m_vBodyVelocity;
    Vec2 m_vHeadVelocity;
    CObject* m_pSelectedHand;

public:
    virtual ~CBossStateChange() {}
    virtual CBossState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

    void    AnimationChange(CEnemyBoss* _pObj);
    void    HandAnimChange(CEnemyBoss* _pObj);

};

