#pragma once
#include "CState.h"
class CEnemyState :
    public CState
{
protected:
    float   m_fCurTime;
    float   m_fDuration;

    bool    m_bOnceFunc;
    float   m_fOnceFuncTime;
    float   m_fOnceFuncCurTime;

public:
    virtual ~CEnemyState() {}
    virtual CState* HandleInput(CObject* _pObj) { return nullptr; }
    virtual void    Update(CObject* _pObj) {}

    virtual void    Enter(CObject* _pObj) {}
    virtual void    Exit(CObject* _pObj) {}
};

