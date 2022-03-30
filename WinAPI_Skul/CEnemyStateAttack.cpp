#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CEnemy.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"

CEnemyState* CEnemyStateAttack::HandleInput(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (m_fAttackLimitTime <= 0)
            return new CEnemyStateIdle();
    }
    break;
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        if (m_fAttackLimitTime <= 0)
            return new CEnemyStateIdle();
    }
    break;
    }
    return nullptr;
}
void CEnemyStateAttack::Update(CObject* _pObj) 
{
    CEnemy* pEnemy = (CEnemy*)_pObj;

    m_fAttackLimitTime -= DT;

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

void CEnemyStateAttack::Enter(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        m_fAttackLimitTime = 0.6f;
        m_fFlowTime = 0.f;
        pEnemy->GetAnimator()->Play(L"BigKnight_AttacKA", true);
        pEnemy->m_strCurState = L"Attack";
        pEnemy->Attack();
        SINGLE(CSoundManager)->Play(L"AttackB");
        break;
    }
    
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        m_fAttackLimitTime = 0.6f;
        m_fFlowTime = 0.f;
        pEnemy->GetAnimator()->Play(L"Wizard_Attack", true);
        pEnemy->Attack();
        pEnemy->m_strCurState = L"Attack";
        break;
    }
    
    }
}

void CEnemyStateAttack::Exit(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        pEnemy->m_bCanAttack = false;
        pEnemy->m_fCurAttackTime = 0.f;
        break;
    }

    case ENEMY_TYPE::WIZARD:
    {
        pEnemy->m_bCanAttack = false;
        pEnemy->m_fCurAttackTime = 0.f;
        break;
    }

    }
}