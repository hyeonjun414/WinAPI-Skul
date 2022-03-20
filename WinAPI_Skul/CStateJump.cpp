#include "pch.h"
#include "CStateJump.h"
#include "CStateIdle.h"
#include "CStateFall.h"
#include "CStateDash.h"
#include "CStateJumpAttack.h"


#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEffect.h"

CState* CStateJump::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
        {
            pPlayer->m_bCanDoubleJump = false;
            return new CStateJump();
        }
        if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
        {
            pPlayer->m_bCanDash = false;
            return new CStateDash();
        }
        if (KEYTAP(KEY::X) && pPlayer->m_bCanJumpAttack)
        {
            return new CStateJumpAttack();
        }
        if (pPlayer->GetVelocity().y <= 0)
            return new CStateFall();
        return nullptr;
    }
    break;
    }
    return nullptr;
}

void CStateJump::Update(CObject* _pObj)
{
    switch (_pObj->GetObjType())
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
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (pPlayer->m_bCanSkill)
            pPlayer->GetAnimator()->Play(L"Player_Jump", true);
        else
            pPlayer->GetAnimator()->Play(L"Player_Jump_Headless", true);
        pPlayer->m_vVelocity.y = 700;
        if (!pPlayer->m_bCanDoubleJump)
        {
            CEffect* eft = new CEffect(OBJ_TYPE::EFFECT, L"Jump_Smoke", L"texture\\effect\\doublejump_smoke.png",
                0.5,0.5, 96, pPlayer->GetObjDir());
            CREATEOBJECT(eft);
            eft->SetPos(pPlayer->GetPos() + Vec2(0, -20));
            SINGLE(CSoundManager)->Play(L"JumpAir");
        }
        else
        {
            SINGLE(CSoundManager)->Play(L"Jump");
        }
    }
    break;
    }
}

void CStateJump::Exit(CObject* _pObj)
{
    CPlayer* pPlayer = (CPlayer*)_pObj;
    //pPlayer->m_bIsGround = false;
}
