#include "pch.h"
#include "Stateheader.h"

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
        SINGLE(CSoundManager)->Play(L"SkillA");
        m_fCurTime = 0.f;
        m_fDuration = 0.5f;
        pPlayer->SkillA();
        pPlayer->m_strCurState = L"SkillA";
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