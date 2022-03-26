#pragma once
#include "CPlayerState.h"
class CPlayerStateIdle :
    public CPlayerState
{
public:
    virtual ~CPlayerStateIdle() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

