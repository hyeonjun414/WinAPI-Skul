#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEffect.h"

CState* CStateJumpAttack::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (m_fJumpAttackCurTime >= m_fJumpAttackLimitTime ||
            pPlayer->m_bIsGround)
            return new CStateIdle();
        return nullptr;
    }
    break;
    }
    return nullptr;
}

void CStateJumpAttack::Update(CObject* _pObj)
{
    switch (_pObj->GetObjType())
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
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_fJumpAttackLimitTime = 0.5f;
        m_fJumpAttackCurTime = 0.f;
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_bCanJumpAttack = false;
        if (pPlayer->m_bCanSkill)
            pPlayer->GetAnimator()->Play(L"Player_JumpAttack", true);
        else
            pPlayer->GetAnimator()->Play(L"Player_JumpAttack_Headless", true);
        pPlayer->JumpAttack();
        SINGLE(CSoundManager)->Play(L"AttackB");
        pPlayer->m_strCurState = L"JumpAttack";
    }
    break;
    }
}

void CStateJumpAttack::Exit(CObject* _pObj)
{
    CPlayer* pPlayer = (CPlayer*)_pObj;
}