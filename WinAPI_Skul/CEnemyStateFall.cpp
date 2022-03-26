#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"
#include "CAnimator.h"
#include "CCollider.h"

CEnemyState* CEnemyStateFall::HandleInput(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
        return new CEnemyStateDie();

    if (pEnemy->m_bIsGround)
        return new CEnemyStateIdle();

    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
    }
    break;
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
    }
    break;
    }
    return nullptr;
}

void CEnemyStateFall::Update(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    pEnemy->m_tEnemyInfo.m_vVelocity.y += 1400 * DT;
    pEnemy->m_vPos.y += pEnemy->m_tEnemyInfo.m_vVelocity.y * DT;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        break;
    }
    
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        break;
    }
    }

}

void CEnemyStateFall::Enter(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        pEnemy->GetAnimator()->Play(L"BigKnight_Idle", true);
        pEnemy->m_strCurState = L"Fall";
        break;
    }
    
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        pEnemy->GetAnimator()->Play(L"Wizard_Idle", true);
        pEnemy->m_strCurState = L"Fall";
        break;
    }
    
    }
}

void CEnemyStateFall::Exit(CObject* _pObj)
{
}
