#pragma once
#include "CObject.h"



class CD2DImage;
class CState;

class CPlayer :
    public CObject
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

protected:
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
    SKUL_TYPE       m_eSkulType;
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
    virtual void        Move(float _speed);
    virtual void        Jump(float _speed);
    virtual void        CoolTime();
    virtual void        Attack() {}
    virtual void        JumpAttack() {}
    virtual void        SkillA() {}
    virtual void        SkillB() {}

    virtual void        Enter() {}
    virtual void        Exit() {}

    virtual void        Hit(int _damage);

    
};

