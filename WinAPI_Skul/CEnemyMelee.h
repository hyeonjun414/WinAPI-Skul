#pragma once
#include "CEnemy.h"
class CEnemyMelee :
    public CEnemy
{
    friend class CEnemyStateIdle;
    friend class CEnemyStateDie;
    friend class CEnemyStateTrace;
    friend class CEnemyStateFall;
public:
    CEnemyMelee(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType);
    virtual ~CEnemyMelee();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    virtual void        Attack();
};

