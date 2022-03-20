#include "pch.h"
#include "CStateSkill.h"
#include "CStateAttack.h"
#include "CStateIdle.h"
#include "CStateMove.h"
#include "CStateJump.h"
#include "CStateFall.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CState* CStateSkill::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;

        if (m_fCurTime >= m_fDuration)
            return new CStateIdle();
        return nullptr;
    }
    break;
    }
    return nullptr;
}
void CStateSkill::Update(CObject* _pObj) {
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_fCurTime += DT;
    }
    break;
    }
}

void CStateSkill::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->GetAnimator()->Play(L"Player_SkillA", true);
        m_fCurTime = 0.f;
        m_fDuration = 0.5f;
        pPlayer->SkillA();
    }
    break;
    }
}

void CStateSkill::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_bCanSkill = false;
        pPlayer->m_fSkillCurTime = 0.f;
    }
    break;
    }
}