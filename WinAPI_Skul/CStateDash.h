#pragma once
#include "CState.h"
class CStateDash :
    public CState
{
private:
    float         m_iDist;
    float         m_iCurMoveDist;
    float           m_fDashSpeed;
    

public:
    CStateDash() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

