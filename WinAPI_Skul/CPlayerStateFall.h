#pragma once
#include "CPlayerState.h"
class CPlayerStateFall :
    public CPlayerState
{
public:
    virtual ~CPlayerStateFall() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

