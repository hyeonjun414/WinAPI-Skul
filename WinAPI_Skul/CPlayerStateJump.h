#pragma once
#include "CPlayerState.h"
class CPlayerStateJump :
    public CPlayerState
{
public:
    virtual ~CPlayerStateJump() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

