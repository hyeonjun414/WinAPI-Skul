#pragma once
#include "CPlayerState.h"
class CPlayerStateDash :
    public CPlayerState
{
private:
    float         m_iDist;
    float         m_iCurMoveDist;
    float         m_fDashSpeed;

public:
    virtual ~CPlayerStateDash() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

