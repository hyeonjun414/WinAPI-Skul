#pragma once
#include "CBossState.h"
class CBossStateSlam :
    public CBossState
{
private:
    Vec2 m_vOriginPos;
    float m_fNextAttackTime;
    float m_fNextAttackCurTime;
    float m_fMoveTime;
    float m_fCurTime;
    float m_fMoveDir;

    bool m_bOnceFunc = false;
    float m_fOnceFuncTime = 0.5f;
    float m_fOnceFuncCurTime = 0.f;

    float m_fSlamTime;
    float m_fSlamCurTime;
    Vec2 m_vSlamVelocity;
    CObject* m_pSelectedHand;

public:
    virtual ~CBossStateSlam() {}
    virtual CBossState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

    void SetSlamVelocity(CObject* _pObj);
    void SelectSlamHand(CObject* _pObj);
};

