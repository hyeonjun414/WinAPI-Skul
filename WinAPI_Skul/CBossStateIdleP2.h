#pragma once
#include "CBossState.h"
class CBossStateIdleP2 :
    public CBossState
{
private:
    Vec2 m_vOriginPos;
    float m_fNextAttackTime;
    float m_fNextAttackCurTime;
    float m_fMoveTime;
    float m_fCurTime;
    float m_fMoveDir;

    BossPattern  m_eNextAction;

public:
    virtual ~CBossStateIdleP2() {}
    virtual CBossState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};
