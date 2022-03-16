#include "pch.h"
#include "CSPlayerIdle.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CSPlayerMove.h"

void CSPlayerIdle::HandleInput(CPlayer* _pPlayer) {
    if (KEYHOLD(KEY::A))
    {
        CPlayerState* state = new CSPlayerMove();
        if (_pPlayer->m_pState != nullptr)
        {
            delete _pPlayer->m_pState;
        }
        _pPlayer->m_pState = state;
        _pPlayer->SetObjDir(false);
        _pPlayer->GetAnimator()->Play(L"Player_Move", true);
    }
    if (KEYHOLD(KEY::D))
    {
        CPlayerState* state = new CSPlayerMove();
        if (_pPlayer->m_pState != nullptr)
        {
            delete _pPlayer->m_pState;
        }
        _pPlayer->m_pState = state;
        _pPlayer->SetObjDir(true);
        _pPlayer->GetAnimator()->Play(L"Player_Move", true);
    }
}
void CSPlayerIdle::Update(CPlayer* _pPlayer) {
}
