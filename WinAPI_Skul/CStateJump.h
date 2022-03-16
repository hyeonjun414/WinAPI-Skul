#pragma once
#include "CState.h"
class CStateJump :
    public CState
{
private:
    Vec2 m_vVelocity;

public:
    CStateJump() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void    Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

    virtual void	OnCollision(CObject* _pObj, CCollider* _pOther) {}
    virtual void	OnCollisionEnter(CObject* _pObj, CCollider* _pOther) {}
    virtual void	OnCollisionExit(CObject* _pObj, CCollider* _pOther) {}

};
