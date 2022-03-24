#pragma once
#include "CObject.h"


//enum class PLAYER_STATE
//{
//    IDLE,
//    MOVE,
//    ATTACK,
//    JUMP,
//    FALL,
//    SKILL,
//    DASH,
//    JUMPATTACK,
//    REBONE,
//    
//};

struct tPlayer_Info
{
    wstring m_strName;
    int     m_iMaxHp;
    int     m_iHp;
    int     m_iDamage;
    int     m_iSkillDamage;
    Vec2    m_vVelocity;
};

class CD2DImage;
class CState;

class CPlayer :
    public CObject
{
    friend class CGameManager;
    friend class CStateIdle;
    friend class CStateMove;
    friend class CStateJump;
    friend class CStateFall;
    friend class CStateAttack;
    friend class CStateJumpAttack;
    friend class CStateDash;
    friend class CStateSkill;
    friend class CStateAppear;

private:
    wstring         m_strCurState;
    Vec2            m_vVelocity;
    bool            m_bIsGround;
    int             m_iCollCount;

    bool            m_bCanDoubleJump;
    bool            m_bCanSecondDash;
    bool            m_bCanDash;
    bool            m_bCanJumpAttack;
    bool            m_bCanSkill;

    float           m_fDashCoolTime;
    float           m_fDashCurTime;

    float           m_fSecondDashCoolTime;
    float           m_fSecondDashCurTime;

    float           m_fSkillCoolTime;
    float           m_fSkillCurTime;

    // 플레이어 전투 정보
    tPlayer_Info    m_tPlayerInfo;

    CObject*        m_pHead; // 스킬에서 사용해서 던진 해골 객체

public:
    CState* m_pState;

public :
    CPlayer(OBJ_TYPE _objGroup);
    virtual ~CPlayer();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther) ;
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    void                SetPlayerInfo(tPlayer_Info _tInfo)  { m_tPlayerInfo = _tInfo; }
    void                SetVelocity(Vec2 _vVelocity)        { m_vVelocity = _vVelocity; }
    void                SetIsGround(bool _bIsGround)        { m_bIsGround = _bIsGround; }
    Vec2                GetVelocity()                       { return m_vVelocity; }
    tPlayer_Info&       GetPlayerInfo()                     { return m_tPlayerInfo; }
    bool                IsGround()                          { return m_bIsGround; }
    float               GetCurHealthRatio()                 { return m_tPlayerInfo.m_iHp / (float)m_tPlayerInfo.m_iMaxHp; }

    void                RenderPlayerInfo();

    void                CoolTime();
    void                Attack();
    void                JumpAttack();
    void                SkillA();
    void                SkillB();

    void                Hit(int _damage);

    
};

