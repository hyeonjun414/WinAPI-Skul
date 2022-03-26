#pragma once
#include "CPlayerState.h"
class CPlayerStateSkillB :
    public CPlayerState
{
private:
    bool    m_bIsAttack;

public:
    virtual ~CPlayerStateSkillB() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);

};

