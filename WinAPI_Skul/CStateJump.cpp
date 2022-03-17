#include "pch.h"
#include "CStateJump.h"
#include "CStateIdle.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateJump::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
        {
            pPlayer->m_bCanDoubleJump = false;
            return new CStateJump();
        }
        if (pPlayer->GetVelocity().y <= 0)
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
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->SetObjDir(false);
            pPlayer->m_vPos.x -= pPlayer->m_vVelocity.x * DT;
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->SetObjDir(true);
            pPlayer->m_vPos.x += pPlayer->m_vVelocity.x * DT;
        }
        pPlayer->m_vVelocity.y -= 1400 * DT;
        pPlayer->m_vPos.y -= pPlayer->m_vVelocity.y * DT;
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
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_Jump", true);
        pPlayer->m_vVelocity.y = 700;
    }
    break;
    }
}

void CStateJump::Exit(CObject* _pObj)
{
    CPlayer* pPlayer = (CPlayer*)_pObj;
    pPlayer->m_bIsGround = false;
}
