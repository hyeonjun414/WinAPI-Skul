#include "pch.h"
#include "CStateAppear.h"
#include "CStateDie.h"
#include "CStateMove.h"
#include "CStateIdle.h"
#include "CStateJump.h"
#include "CStateFall.h"
#include "CStateJumpAttack.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

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
    case OBJ_TYPE::ENEMY_MELEE:
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
    case OBJ_TYPE::ENEMY_MELEE:
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
        CPlayer* pPlayer = (CPlayer*)_pObj;
        pPlayer->SkillB();
        m_fCurTime = 0.f;
        m_fDuration = 0.5f;
        pPlayer->GetAnimator()->Play(L"Player_SkillRebone", true);
    }
    break;
    case OBJ_TYPE::ENEMY_MELEE:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        m_fCurTime = 0.f;
        m_fDuration = 1.0f;
        
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
    }
    break;
    case OBJ_TYPE::ENEMY_MELEE:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
    }
    break;
    }
}
