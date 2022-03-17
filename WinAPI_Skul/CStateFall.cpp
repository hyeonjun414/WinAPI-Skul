#include "pch.h"

#include "CStateMove.h"
#include "CStateIdle.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateFall::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (pPlayer->IsGround())
            return new CStateIdle();

        if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
        {
            pPlayer->m_bCanDoubleJump = false;
            return new CStateJump();
        }
        return nullptr;
    }
    break;
    }
}

void CStateFall::Update(CObject* _pObj)
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

        if (pPlayer->m_vVelocity.y < -1)
        {
            pPlayer->GetAnimator()->Play(L"Player_Fall", true);
        }
        if (pPlayer->m_vVelocity.y < -200)
        {
            pPlayer->GetAnimator()->Play(L"Player_FallRepeat", true);
        }
    }
    break;
    }

}

void CStateFall::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_bIsFloor = false;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_Fall", true);
    }
    break;
    }
}

void CStateFall::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_vVelocity.y = 0;
    }
    break;
    }
}
