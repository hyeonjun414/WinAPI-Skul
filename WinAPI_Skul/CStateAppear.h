#pragma once
#include "CState.h"
class CStateAppear :
    public CState
{
private:
    float m_fCurTime;
    float m_fDuration;

public:
    CStateAppear() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

