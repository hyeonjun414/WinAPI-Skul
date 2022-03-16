#pragma once
#include "CPlayerState.h"

class CSPlayerIdle :
    public CPlayerState
{
public:
    CSPlayerIdle() {}

    virtual void HandleInput(CPlayer* _pPlayer);
    virtual void Update(CPlayer* _pPlayer);
};

