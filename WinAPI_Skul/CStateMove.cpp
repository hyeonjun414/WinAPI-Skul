#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateMove::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (KEYAWAY(KEY::LEFT))
        {
            return new CStateIdle();
        }
        if (KEYAWAY(KEY::RIGHT))
        {
            return new CStateIdle();
        }
        if (KEYTAP(KEY::A) && pPlayer->m_bCanSkill)
        {
            return new CStateSkill();
        }
        if (KEYTAP(KEY::S) && !pPlayer->m_bCanSkill)
        {
            return new CStateAppear();
        }
        if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
        {
            pPlayer->m_bCanDash = false;
            return new CStateDash();
        }
        if (KEYTAP(KEY::X))
        {
            return new CStateAttack();
        }
        if (KEYTAP(KEY::C))
        {
            return new CStateJump();
        }
        if (!pPlayer->IsGround())
            return new CStateFall();
        return nullptr;
    }
    break;
    }
    return nullptr;
}
void CStateMove::Update(CObject* _pObj) {

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
    }
        break;
    }
}

void CStateMove::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        
        if (pPlayer->m_bCanSkill)
            pPlayer->GetAnimator()->Play(L"Player_Move", true);
        else
            pPlayer->GetAnimator()->Play(L"Player_Move_Headless", true);
        pPlayer->m_strCurState = L"Move";
    }
    break;
    }
}

void CStateMove::Exit(CObject* _pObj)
{
}
