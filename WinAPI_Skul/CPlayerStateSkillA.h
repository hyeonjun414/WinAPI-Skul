#pragma once
#include "CPlayerState.h"
class CPlayerStateSkillA :
    public CPlayerState
{
private:
    bool    m_bIsAttack;
public:
    virtual ~CPlayerStateSkillA() {}
    virtual CPlayerState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);
};

