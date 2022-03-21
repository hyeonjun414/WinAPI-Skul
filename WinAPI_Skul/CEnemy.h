#pragma once
#include "CObject.h"


struct tEnemy_Info
{
    wstring m_strName;
    int     m_iMaxHp;
    int     m_iHp;
    int     m_iDamage;
    int     m_iSkillDamage;
    int         m_iDetectDist;
    Vec2        m_vVelocity;
    Vec2        m_vAttackPos;
    Vec2        m_vAttackArea;
};

class CState;

class CEnemy :
    public CObject
{
    friend class CStateIdle;
    friend class CStateDie;
    friend class CStateTrace;
    friend class CStateFall;
    friend class CStateAppear;
    friend class CStateAttack;
protected:
    wstring m_strCurState;
    bool    m_bIsGround;
    int     m_iCollCount;

    float       m_fAttackDeleyTime;
    float       m_fCurAttackTime;

    float       m_fHitDelayTime;
    float       m_fCurHitTime;
    bool        m_bCanHit;

    ENEMY_TYPE  m_eEnemyType;
    CState*     m_pState;
    tEnemy_Info m_tEnemyInfo;

public:
    CEnemy(OBJ_TYPE _eType, ENEMY_TYPE _eMonsterType);
    virtual ~CEnemy();

    

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	OnCollision(CCollider* _pOther);
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther);


    ENEMY_TYPE          GetEnemyType()                      { return m_eEnemyType; }
    tEnemy_Info&        GetEnemyInfo()                      { return m_tEnemyInfo; }

    void                SetEnemyInfo(tEnemy_Info _tInfo) { m_tEnemyInfo = _tInfo; }
    bool                CanHit() { return m_bCanHit; }

    void                RenderEnemyInfo();
};

