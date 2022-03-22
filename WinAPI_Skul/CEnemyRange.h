#pragma once
#include "CEnemy.h"
class CEnemyRange :
    public CEnemy
{
    friend class CStateIdle;
    friend class CStateDie;
    friend class CStateTrace;
    friend class CStateFall;
public:
    CEnemyRange(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType);
    virtual ~CEnemyRange();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);


    virtual void        Attack();
    void                Teleport(Vec2 _vTargerPos);
};

