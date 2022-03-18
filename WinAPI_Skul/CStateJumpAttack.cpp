#include "pch.h"
#include "CStateJumpAttack.h"
#include "CStateJump.h"
#include "CStateIdle.h"
#include "CStateFall.h"
#include "CStateDash.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEffect.h"

CState* CStateJumpAttack::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (m_fJumpAttackCurTime >= m_fJumpAttackLimitTime)
            return new CStateIdle();
        return nullptr;
    }
    break;
    }
    return nullptr;
}

void CStateJumpAttack::Update(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->m_vPos.x -= pPlayer->m_vVelocity.x * DT;
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->m_vPos.x += pPlayer->m_vVelocity.x * DT;
        }
        pPlayer->m_vVelocity.y -= 1400 * DT;
        pPlayer->m_vPos.y -= pPlayer->m_vVelocity.y * DT;

        m_fJumpAttackCurTime += DT;
    }
    break;
    }
}

void CStateJumpAttack::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjGroup())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_fJumpAttackLimitTime = 0.5f;
        m_fJumpAttackCurTime = 0.f;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_JumpAttack", true);
        SINGLE(CSoundManager)->Play(L"AttackB");
    }
    break;
    }
}

void CStateJumpAttack::Exit(CObject* _pObj)
{
    CPlayer* pPlayer = (CPlayer*)_pObj;
}