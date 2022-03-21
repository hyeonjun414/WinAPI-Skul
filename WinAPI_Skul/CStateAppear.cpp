#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEffect.h"

#include "CEnemyMelee.h"

CState* CStateAppear::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (m_fCurTime >= m_fDuration)
            return new CStateIdle();
    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (m_fCurTime >= m_fDuration)
            return new CStateIdle();
    }
    break;
    }
    return nullptr;
}

void CStateAppear::Update(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_fCurTime += DT;
    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        m_fCurTime += DT;

    }
    break;
    }
}

void CStateAppear::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        m_fCurTime = 0.f;
        m_fDuration = 0.5f;

        CPlayer* pPlayer = (CPlayer*)_pObj;
        CEffect* eft = new CEffect(OBJ_TYPE::EFFECT, L"DisAppear", L"texture\\effect\\Enemy_Dead.png", 0.5f, 0.5f, 128, pPlayer->GetObjDir());
        CREATEOBJECT(eft);
        eft->SetPos(pPlayer->GetPos());
        
        pPlayer->SkillB();

        eft = new CEffect(OBJ_TYPE::EFFECT, L"Appear", L"texture\\effect\\Enemy_Appearance.png", 0.5f, 0.5f, 128, pPlayer->GetObjDir());
        eft->SetPos(pPlayer->GetPos());
        CREATEOBJECT(eft);
        
        pPlayer->GetAnimator()->Play(L"Player_SkillRebone", true);
        SINGLE(CSoundManager)->Play(L"SkillB");

        pPlayer->m_strCurState = L"SkillB";

        
    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        CEnemy* pEnemy = (CEnemy*)_pObj;
        m_fCurTime = 0.f;
        m_fDuration = 1.0f;
        pEnemy->m_strCurState = L"Appear";
        pEnemy->GetAnimator()->Play(L"AppearEnemy", false);
    }
    break;
    }
}

void CStateAppear::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->m_vVelocity.y = 0;
       

    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
    }
    break;
    }
}
