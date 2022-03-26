#pragma once
#include "CBossState.h"
class CBossStateDie :
    public CBossState
{
private:
    Vec2 m_vOriginPos;
    float m_fNextAttackTime;
    float m_fNextAttackCurTime;
    float m_fMoveTime;
    float m_fCurTime;
    float m_fMoveDir;

    bool m_bOnceFunc;
    float m_fOnceFuncTime;
    float m_fOnceFuncCurTime;

public:
    virtual ~CBossStateDie() {}
    virtual CBossState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

    void    AnimationChange(CEnemyBoss* _pObj);
};

