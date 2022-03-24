#pragma once
#include "CEnemy.h"
class CEnemyBoss :
    public CEnemy
{
    friend class CBossStateIdle;
    friend class CBossStateSlam;
    friend class CBossStateSweep;
    friend class CBossStateChange;
    friend class CBossStateBomb;
    friend class CBossStateIdleP2;

private:
    CObject* m_pBody;
    CObject* m_pLeftHand;
    CObject* m_pRightHand;
    CObject* m_pHeadTop;
    CObject* m_pHeadBottom;

    float m_fMoveTime;
    float m_fMoveCurTime;
    float m_fHandMoveCurTime;
    float moveSwitch = -1.f;

    bool m_bIsPhaseChanged;

    

public:
    CEnemyBoss(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType);
    virtual ~CEnemyBoss();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    virtual void        Hit(int _damage);

    void        Slam(CObject* _pObj);
    void        Sweep(CObject* _pObj);
};

