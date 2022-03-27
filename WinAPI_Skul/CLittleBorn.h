#pragma once
#include "CPlayer.h"
class CLittleBorn :
    public CPlayer
{
public:
    CLittleBorn(OBJ_TYPE _eType);
    virtual ~CLittleBorn();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    virtual void        CoolTime();
    virtual void        Attack();
    virtual void        JumpAttack();
    virtual void        SkillA();
    virtual void        SkillB();

    virtual void        Hit(int _damage);

    virtual void        Enter();
    virtual void        Exit();
};

