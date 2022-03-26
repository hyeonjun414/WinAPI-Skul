#pragma once
#include "CObject.h"
#include "CHealthBar.h"

struct tEnemy_Info
{
    int         m_iMaxHp;
    int         m_iHp;
    int         m_iDamage;
    int         m_iSkillDamage;
    int         m_iDetectDist;
    int         m_iAttackDist;
    Vec2        m_vVelocity;
    Vec2        m_vAttackPos;
    Vec2        m_vAttackArea;
};

class CState;

class CEnemy :
    public CObject
{
    friend class CEnemyStateIdle;
    friend class CEnemyStateDie;
    friend class CEnemyStateTrace;
    friend class CEnemyStateFall;
    friend class CEnemyStateAppear;
    friend class CEnemyStateAttack;
protected:
    wstring m_strCurState;
    bool    m_bIsGround;
    int     m_iCollCount;

    float       m_fAttackDeleyTime;
    float       m_fCurAttackTime;

    float       m_fHitDelayTime;
    float       m_fCurHitTime;
    bool        m_bCanHit;

    float       m_fTraceCoolTime;
    float       m_fCurTraceTime;
    bool        m_bCanTrace;

    ENEMY_TYPE  m_eEnemyType;
    CState*     m_pState;
    tEnemy_Info m_tEnemyInfo;

    // ÄÄÆ÷³ÍÆ®
    CHealthBar* m_pHpBar;

public:
    CEnemy(OBJ_TYPE _eType);
    CEnemy(OBJ_TYPE _eType, ENEMY_TYPE _eMonsterType);
    virtual ~CEnemy();

    

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    virtual void        Attack() {}
    virtual void        Hit(int _damage);
    virtual void        Die();


    ENEMY_TYPE          GetEnemyType()                      { return m_eEnemyType; }
    tEnemy_Info&        GetEnemyInfo()                      { return m_tEnemyInfo; }

    void                SetEnemyInfo(tEnemy_Info _tInfo) { m_tEnemyInfo = _tInfo; }
    bool                CanHit() { return m_bCanHit; }

    void                RenderEnemyInfo();
    void                CoolTime();

    void CreateHealthBar();
    
};

