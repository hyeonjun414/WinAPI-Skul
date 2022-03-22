#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CEnemyMelee.h"
#include "CEnemyRange.h"

CState* CStateTrace::HandleInput(CObject* _pObj)
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
            if (abs(PLAYERPOS.x - pEnemy->GetPos().x) < 100 &&
                abs(PLAYERPOS.y - pEnemy->GetPos().y) < 50)
                     return new CStateAttack();
            if (abs(PLAYERPOS.x - pEnemy->GetPos().x) > 400)
                return new CStateIdle();

            if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
                return new CStateDie();
            if (!pEnemy->m_bIsGround)
                return new CStateFall();
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            if (abs(PLAYERPOS.x - pEnemy->GetPos().x) < 400 &&
                abs(PLAYERPOS.y - pEnemy->GetPos().y) < 200)
                return new CStateAttack();
            if (abs(PLAYERPOS.x - pEnemy->GetPos().x) > 600)
                return new CStateIdle();

            if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
                return new CStateDie();
            if (!pEnemy->m_bIsGround)
                return new CStateFall();
        }
        break;
        }

    }
    break;
    }
    return nullptr;
}

void CStateTrace::Update(CObject* _pObj)
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
            if (PLAYERPOS.x > pEnemy->GetPos().x +1)
            {
                pEnemy->SetObjDir(true);
                pEnemy->m_vPos.x += pEnemy->m_tEnemyInfo.m_vVelocity.x * DT;
            }
            else if(PLAYERPOS.x < pEnemy->GetPos().x -1)
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
    break;
    }
}

void CStateTrace::Enter(CObject* _pObj)
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
            pEnemy->GetAnimator()->Play(L"BigKnight_Move", true);
            pEnemy->m_strCurState = L"Trace";
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            pEnemy->GetAnimator()->Play(L"Wizard_Teleport", true);
            pEnemy->m_strCurState = L"Trace";
        }
        break;
        }
        
    }
    break;
    }
}

void CStateTrace::Exit(CObject* _pObj)
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
            ;
        }
        break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            ;
        }
        break;
        }
    }
    break;
    }
}
