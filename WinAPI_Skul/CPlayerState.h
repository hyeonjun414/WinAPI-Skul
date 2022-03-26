#pragma once
#include "CState.h"
class CPlayerState :
    public CState
{
protected:
    float m_fCurTime;
    float m_fDuration;

    bool m_bOnceFunc;
    float m_fOnceFuncTime;
    float m_fOnceFuncCurTime;

public:
    virtual ~CPlayerState() {}
    virtual CPlayerState* HandleInput(CObject* _pObj) { return nullptr; }
    virtual void Update(CObject* _pObj) {}

    virtual void Enter(CObject* _pObj) {}
    virtual void Exit(CObject* _pObj) {}
};

