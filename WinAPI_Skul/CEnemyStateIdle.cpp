#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CEnemyMelee.h"
#include "CEnemyRange.h"


CEnemyState* CEnemyStateIdle::HandleInput(CObject* _pObj) {
    
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
            return new CEnemyStateDie();

        if (abs(PLAYERPOS.x - pEnemy->GetPos().x) < 400 && pEnemy->m_bIsGround)
            return new CEnemyStateTrace();

        if (!pEnemy->m_bIsGround)
            return new CEnemyStateFall();

        break;
    }
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
            return new CEnemyStateDie();

        if (!pEnemy->m_bIsGround)
            return new CEnemyStateFall();

        // 플레이어와의 거리가 400이상으로 벌어지고 추적 가능 상태이면 텔레포트
        if ((PLAYERPOS - pEnemy->GetPos()).Length() > 400 &&
            pEnemy->m_bIsGround && pEnemy->m_bCanTrace)
        {
            pEnemy->m_bCanTrace = false;
            return new CEnemyStateTrace();
        }


        if ((PLAYERPOS - pEnemy->GetPos()).Length() < 400 &&
            pEnemy->m_bCanAttack)
            return new CEnemyStateAttack();

        break;
    }
    
    }

    return nullptr;
}
void CEnemyStateIdle::Update(CObject* _pPlayer) {
}

void CEnemyStateIdle::Enter(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        pEnemy->GetAnimator()->Play(L"BigKnight_Idle", true);
        pEnemy->m_strCurState = L"Idle";
    }
    break;
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        pEnemy->GetAnimator()->Play(L"Wizard_Idle", true);
        pEnemy->m_strCurState = L"Idle";
    }
    break;
    }
}

void CEnemyStateIdle::Exit(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
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



