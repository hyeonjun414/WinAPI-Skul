#pragma once
#include "CState.h"
class CStateJump :
    public CState
{
public:
    CStateJump() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void    Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

};

