#pragma once
#include "CState.h"
class CStateFall :
    public CState
{
private:
public:
    CStateFall() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);


};

