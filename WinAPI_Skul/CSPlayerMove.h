#pragma once
#include "CPlayerState.h"

class CSPlayerMove :
    public CPlayerState
{

public:
    CSPlayerMove():CPlayerState() {}

    virtual void HandleInput(CPlayer* _pPlayer);
    virtual void Update(CPlayer* _pPlayer);
};

