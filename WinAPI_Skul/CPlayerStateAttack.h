#pragma once
#include "CPlayerState.h"
class CPlayerStateAttack :
    public CPlayerState
{
private:
    float   m_fAttackTime;
    float   m_fAttackCurTime;

    float   m_fAttackDelay;
    int     m_iAttackCount;

    bool    m_bAttackInput;
    bool    m_bIsSecondAttack;

    bool    m_bIsAttack;
    bool    m_IsOtherAnim;
    float   m_fOtherAnimTime;

public:
    virtual ~CPlayerStateAttack() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

