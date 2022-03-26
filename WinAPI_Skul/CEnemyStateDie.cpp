#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CEnemyMelee.h"
#include "CEnemyRange.h"

CEnemyState* CEnemyStateDie::HandleInput(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
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
            if (m_fCurTime >= m_fDuration)
            {
                pEnemy->Die();
            }
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            if (m_fCurTime >= m_fDuration)
            {
                pEnemy->Die();
            }
        }
        break;
        }
    }
    break;
    }
    return nullptr;
}

void CEnemyStateDie::Update(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
    }
    break;
    case OBJ_TYPE::ENEMY:
    {
        m_fCurTime += DT;
        CEnemy* pEnemy = (CEnemy*)_pObj;
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
    }
    break;
    }
}

void CEnemyStateDie::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
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
            m_fCurTime = 0.f;
            m_fDuration = 1.0f;
            //pEnemy->GetAnimator()->Play(L"BigKnight_Die", true);
            pEnemy->GetAnimator()->PlayAndNextAnim(L"BigKnight_Die", false, L"DisappearEnemy");
        }
            break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            m_fCurTime = 0.f;
            m_fDuration = 1.0f;
            //pEnemy->GetAnimator()->Play(L"BigKnight_Die", true);
            pEnemy->GetAnimator()->PlayAndNextAnim(L"Wizard_Idle", false, L"DisappearEnemy");
        }
        break;
        }
    }
    break;
    }
}

void CEnemyStateDie::Exit(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
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
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
        }
        break;
        }
    }
    break;
    }
}
