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

    if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
        return new CEnemyStateDie();

    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        if (m_fCurTime >= m_fDuration)
            return new CEnemyStateIdle();
    }
    break;
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        if (m_fCurTime >= m_fDuration)
            return new CEnemyStateIdle();

    }
    break;
    }
    return nullptr;
}
void CEnemyStateAttack::Update(CObject* _pObj) 
{
    CEnemy* pEnemy = (CEnemy*)_pObj;

    m_fCurTime += DT;
    if (!m_bOnceFunc)
    {
        m_fOnceFuncCurTime += DT;
        if (m_fOnceFuncCurTime >= m_fOnceFuncTime)
        {
            m_bOnceFunc = true;
            m_fOnceFuncCurTime = 0;
        }
    }
    switch (pEnemy->GetEnemyType())
    {
    case ENEMY_TYPE::BIG_KNIGHT:
    {
        CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
        switch (m_iAttackType)
        {
        case 0:
        {
            if (1.0f < m_fCurTime && m_fCurTime < 1.1f && m_bOnceFunc)
            {
                m_bOnceFunc = false;
                pEnemy->Attack();
            }
            break;
        }
        case 1:
        {
            if (1.5f < m_fCurTime && m_fCurTime < 1.6f && m_bOnceFunc)
            {
                m_bOnceFunc = false;
                pEnemy->Tackle();
            }
            if (1.6f < m_fCurTime)
            {
                pEnemy->SetPos(pEnemy->GetPos()+ Vec2(pEnemy->GetObjDir() ? 400*DT : -400 * DT, 0));
            }
            break;
        }
        }
        break;
    }
    
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        if (m_bOnceFunc)
        {
            m_bOnceFunc = false;
            pEnemy->Attack();
        }
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
        m_iAttackType = rand() % 2;
        pEnemy->SetObjDir(PLAYERPOS.x > pEnemy->GetPos().x);
        switch (m_iAttackType)
        {
        case 0:
        {
            m_fDuration = 2.0f;
            m_fCurTime = 0.f;
            m_bOnceFunc = true;
            m_fOnceFuncTime = 0.2f;
            m_fOnceFuncCurTime = 0.f;

            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
            pEnemy->GetAnimator()->Play(L"BigKnight_AttacKA", true);
            pEnemy->m_strCurState = L"SMASH";
            SINGLE(CSoundManager)->Play(L"AttackB");
            break;
        }
        case 1:
        {
            m_fDuration = 2.5f;
            m_fCurTime = 0.f;
            m_bOnceFunc = true;
            m_fOnceFuncTime = 0.2f;
            m_fOnceFuncCurTime = 0.f;

            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
            
            pEnemy->GetAnimator()->Play(L"BigKnight_AttacKB", true);
            SINGLE(CSoundManager)->Play(L"AttackB");
            
            pEnemy->m_strCurState = L"TACKLE";
            break;
        }
        }
        break;
    }
    
    case ENEMY_TYPE::WIZARD:
    {
        CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        m_fDuration = 3.f;
        m_fCurTime = 0.f;
        m_bOnceFunc = false;
        m_fOnceFuncTime = 1.0f;
        m_fOnceFuncCurTime = 0.f;
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