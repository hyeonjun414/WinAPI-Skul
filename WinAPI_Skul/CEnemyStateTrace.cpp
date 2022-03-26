#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CEnemyMelee.h"
#include "CEnemyRange.h"

CEnemyState* CEnemyStateTrace::HandleInput(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (abs(PLAYERPOS.x - pEnemy->GetPos().x) < 100 &&
            abs(PLAYERPOS.y - pEnemy->GetPos().y) < 50)
            return new CEnemyStateAttack();
        if (abs(PLAYERPOS.x - pEnemy->GetPos().x) > 400)
            return new CEnemyStateIdle();

        if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
            return new CEnemyStateDie();
        if (!pEnemy->m_bIsGround)
            return new CEnemyStateFall();
    }
    break;
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;

        if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
            return new CEnemyStateDie();

        if (!pEnemy->m_bIsGround)
            return new CEnemyStateFall();
        if ((PLAYERPOS - pEnemy->GetPos()).Length() < 400)
            return new CEnemyStateAttack();

        if ((PLAYERPOS - pEnemy->GetPos()).Length() > 600)
            return new CEnemyStateIdle();

        break;
    }
    }
    return nullptr;
}

void CEnemyStateTrace::Update(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (PLAYERPOS.x > pEnemy->GetPos().x + 1)
        {
            pEnemy->SetObjDir(true);
            pEnemy->m_vPos.x += pEnemy->m_tEnemyInfo.m_vVelocity.x * DT;
        }
        else if (PLAYERPOS.x < pEnemy->GetPos().x - 1)
        {
            pEnemy->SetObjDir(false);
            pEnemy->m_vPos.x -= pEnemy->m_tEnemyInfo.m_vVelocity.x * DT;
        }

    }
    break;
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
    }
    break;
    }
}

void CEnemyStateTrace::Enter(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        pEnemy->GetAnimator()->Play(L"BigKnight_Move", true);
        pEnemy->m_strCurState = L"Trace";
        break;
    }
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        SINGLE(CGameManager)->CreateEffect(L"DisAppear", L"texture\\effect\\Enemy_Dead.png",
            pEnemy->GetPos(), 0.5f, 0.5f, pEnemy->GetObjDir());

        pEnemy->Teleport(PLAYERPOS);

        SINGLE(CGameManager)->CreateEffect(L"Appear", L"texture\\effect\\Enemy_Appearance.png",
            pEnemy->GetPos(), 0.5f, 0.5f, pEnemy->GetObjDir());
        pEnemy->GetAnimator()->Play(L"Wizard_Teleport", true);
        pEnemy->m_strCurState = L"Trace";
        break;
    }
    }
}

void CEnemyStateTrace::Exit(CObject* _pObj)
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
