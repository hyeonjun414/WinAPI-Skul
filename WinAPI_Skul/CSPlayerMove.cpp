#include "pch.h"
#include "CSPlayerMove.h"
#include "CSPlayerIdle.h"
#include "CPlayer.h"
#include "CAnimator.h"

void CSPlayerMove::HandleInput(CPlayer* _pPlayer) {
    if (KEYAWAY(KEY::A))
    {
        CPlayerState* state = new CSPlayerIdle();
        if (_pPlayer->m_pState != nullptr)
        {
            delete _pPlayer->m_pState;
        }
        _pPlayer->m_pState = state;
        _pPlayer->SetObjDir(false);
        _pPlayer->GetAnimator()->Play(L"Player_Idle", true);
    }
    if (KEYAWAY(KEY::D))
    {
        CPlayerState* state = new CSPlayerIdle();
        if (_pPlayer->m_pState != nullptr)
        {
            delete _pPlayer->m_pState;
        }
        _pPlayer->m_pState = state;
        _pPlayer->SetObjDir(true);
        _pPlayer->GetAnimator()->Play(L"Player_Idle", true);
        
    }
}
void CSPlayerMove::Update(CPlayer* _pPlayer) {
    if (KEYHOLD(KEY::A))
    {
        _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(-300 * DT, 0));
    }
    if (KEYHOLD(KEY::D))
    {
        _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(300 * DT, 0));
    }
}

