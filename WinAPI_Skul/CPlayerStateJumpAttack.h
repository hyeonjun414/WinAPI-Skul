#pragma once
#include "CPlayerState.h"
class CPlayerStateJumpAttack :
    public CPlayerState
{
public:
    virtual ~CPlayerStateJumpAttack() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

