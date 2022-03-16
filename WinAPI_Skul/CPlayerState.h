#pragma once
#include "CState.h"

class CPlayer;

class CPlayerState :
    public CState
{
public :

    virtual ~CPlayerState() {}
    virtual void HandleInput(CPlayer* _pPlayer) {}
    virtual void Update(CPlayer* _pPlayer) {}
};

