#pragma once
#include "CEnemy.h"
class CEnemyBoss :
    public CEnemy
{
    friend class CBossStateIdle;
    friend class CBossStateSlam;
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

    

public:
    CEnemyBoss(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType);
    virtual ~CEnemyBoss();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    void        Slam(CObject* _pObj);
};

