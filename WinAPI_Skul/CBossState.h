#pragma once
#include "CState.h"
class CBossState :
    public CState
{
public:
    virtual ~CBossState() {}
    virtual CBossState* HandleInput(CObject* _pObj) { return nullptr; }
    virtual void Update(CObject* _pObj) {}

    virtual void Enter(CObject* _pObj) {}
    virtual void Exit(CObject* _pObj) {}

};

