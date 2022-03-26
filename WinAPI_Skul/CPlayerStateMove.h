#pragma once
#include "CPlayerState.h"
class CPlayerStateMove :
    public CPlayerState
{
public:
    virtual ~CPlayerStateMove() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

