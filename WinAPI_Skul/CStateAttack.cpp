#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CEnemy.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"

CState* CStateAttack::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        
        // 공격 시간이 종료되었거나, 마지막 모션이 끝났을때
        if (m_fAttackLimitTime <= 0 || m_iAttackCount == 2)
            return new CStateIdle();

        if (KEYTAP(KEY::X))
            m_bAttackInput = true;

        return nullptr;
    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        CEnemy* pEnemy = (CEnemy*)_pObj;
        switch (pEnemy->GetEnemyType())
        {
        case ENEMY_TYPE::BIG_KNIGHT:
        {
            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
            if (m_fAttackLimitTime <= 0)
                return new CStateIdle();
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            if (m_fAttackLimitTime <= 0)
                return new CStateIdle();
        }
        break;
        }
        
    }
    break;
    }
    return nullptr;
}
void CStateAttack::Update(CObject* _pObj) {
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_fFlowTime += DT;
        m_fAttackLimitTime -= DT;
        if (m_fFlowTime >= m_fAttackDelay && m_bAttackInput)
        {
            m_fFlowTime = 0;
            m_iAttackCount++;
            m_bAttackInput = false;
            m_fAttackLimitTime += m_fAttackDelay;
        }

        if (1 == m_iAttackCount && !m_bIsSecondAttack)
        {
            m_bIsSecondAttack = true;
            if (pPlayer->m_bCanSkill)
                pPlayer->GetAnimator()->Play(L"Player_AttackB", true);
            else
                pPlayer->GetAnimator()->Play(L"Player_AttackB_Headless", true);
            SINGLE(CSoundManager)->Play(L"AttackB");
            
            if (KEYHOLD(KEY::LEFT))
            {
                pPlayer->m_bIsRight = false;
                pPlayer->m_vPos.x -= 30;
            }
            if (KEYHOLD(KEY::RIGHT))
            {
                pPlayer->m_bIsRight = true;
                pPlayer->m_vPos.x += 30;
            }
            pPlayer->Attack();
        }

    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        CEnemy* pEnemy = (CEnemy*)_pObj;
        switch (pEnemy->GetEnemyType())
        {
        case ENEMY_TYPE::BIG_KNIGHT:
        {
            CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
            m_fAttackLimitTime -= DT;
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            m_fAttackLimitTime -= DT;
        }
        break;
        }
    }
    break;
    }
}

void CStateAttack::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        m_fAttackDelay = 0.5f;
        m_fAttackLimitTime = m_fAttackDelay;
        m_iAttackCount = 0;
        m_fFlowTime = 0;
        m_bIsSecondAttack = false;
        m_bAttackInput = false;
        if (pPlayer->m_bCanSkill)
            pPlayer->GetAnimator()->Play(L"Player_AttackA", true);
        else
            pPlayer->GetAnimator()->Play(L"Player_AttackA_Headless", true);
        SINGLE(CSoundManager)->Play(L"AttackA");
        pPlayer->Attack();

        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->m_bIsRight = false;
            pPlayer->m_vPos.x -= 20;
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->m_bIsRight = true;
            pPlayer->m_vPos.x += 20;
        }
        pPlayer->m_strCurState = L"Attack";
    }
    break;
    case OBJ_TYPE::ENEMY:
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
            SINGLE(CSoundManager)->Play(L"AttackB");
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            m_fAttackLimitTime = 0.6f;
            m_fFlowTime = 0.f;
            pEnemy->GetAnimator()->Play(L"Wizard_Attack", true);
            pEnemy->Attack();
            pEnemy->m_strCurState = L"Attack";
        }
        break;
        }
        
    }
    break;
    }
}

void CStateAttack::Exit(CObject* _pObj)
{
}