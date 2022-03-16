#pragma once

enum class STATE_TYPE
{
    IDLE,
    MOVE,
    GROUND,
    JUMP,
    FALL,
    HIT,
    ATTACK,
    TRACE,
    SKILL,
    SWITCH,
};



class CState
{
public :
    virtual ~CState() {}
    virtual CState* HandleInput(CObject* _pObj) { return nullptr; }
    virtual void Update(CObject* _pObj) {}

    virtual void Enter(CObject* _pObj) {}
    virtual void Exit(CObject* _pObj) {}

    virtual void	OnCollision(CObject* _pObj, CCollider* _pOther) {}
    virtual void	OnCollisionEnter(CObject* _pObj, CCollider* _pOther) {}
    virtual void	OnCollisionExit(CObject* _pObj, CCollider* _pOther) {}
};

