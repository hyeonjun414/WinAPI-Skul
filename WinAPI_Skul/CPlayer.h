#pragma once
#include "CObject.h"


enum class PLAYER_STATE
{
    IDLE,
    MOVE,
    ATTACK,
    JUMP,
    FALL,
};

class CD2DImage;
class CState;

class CPlayer :
    public CObject
{
    friend class CStateIdle;
    friend class CStateMove;
    friend class CStateJump;
    friend class CStateFall;
private:
    Vec2    m_vVelocity;
    bool    m_bIsGround;
    bool    m_bIsJumping;
    int     m_iCollCount;

public:
    CState* m_pState;

public :
    CPlayer();
    CPlayer(OBJ_TYPE _objGroup);
    virtual ~CPlayer();
    CLONE(CPlayer)

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther) ;
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    void                AddCollCount(int _i)    { m_iCollCount += _i; }
    int                 GetCollCount()          { return m_iCollCount; }

    void                SetVelocity(Vec2 _vVelocity)   { m_vVelocity = _vVelocity; }
    void                SetIsGround(bool _bIsGround)   { m_bIsGround = _bIsGround; }
    Vec2                GetVelocity()                  { return m_vVelocity; }
    bool                IsGround()                     { return m_bIsGround; }
    
    
};

