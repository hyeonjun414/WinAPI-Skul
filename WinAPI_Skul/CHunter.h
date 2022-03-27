#pragma once
#include "CPlayer.h"
class CHunter :
    public CPlayer
{
    friend class CGameManager;
    friend class CPlayerStateIdle;
    friend class CPlayerStateMove;
    friend class CPlayerStateJump;
    friend class CPlayerStateFall;
    friend class CPlayerStateJumpAttack;
    friend class CPlayerStateSkillA;
    friend class CPlayerStateSkillB;
    friend class CPlayerStateDash;
    friend class CPlayerStateAttack;


private:
    bool    m_bCharged;
    float   m_fChargeTime;
    float   m_fCurChargeTime;
public:
    CHunter(OBJ_TYPE _eType);
    virtual ~CHunter();

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

