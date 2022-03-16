#include "pch.h"
#include "CStateJump.h"
#include "CPlayer.h"
#include "CAnimator.h"

#include "CStateIdle.h"
#include "CStateFall.h"

CState* CStateJump::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* _pPlayer = (CPlayer*)_pObj;
        if (KEYTAP(KEY::SPACE))
        {
            
        }
        if (m_vVelocity.y <= 0)
            return new CStateFall();
        return nullptr;
    }
    break;
    }
}

void CStateJump::Update(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* _pPlayer = (CPlayer*)_pObj;

        if (KEYHOLD(KEY::LEFT))
        {
            _pPlayer->SetObjDir(false);
            _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(-300 * DT, 0));
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            _pPlayer->SetObjDir(true);
            _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(300 * DT, 0));
        }
        m_vVelocity.y -= 700 * DT;
        _pPlayer->SetPos(_pPlayer->GetPos() + Vec2(0, -m_vVelocity.y * DT));
    }
    break;
    }
}

void CStateJump::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_vVelocity.y = 500;
        CPlayer* _pPlayer = (CPlayer*)_pObj;
        _pPlayer->GetAnimator()->Play(L"Player_Jump", true);
    }
    break;
    }
}

void CStateJump::Exit(CObject* _pObj)
{
}
