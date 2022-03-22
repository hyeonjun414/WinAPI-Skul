#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CEnemyMelee.h"
#include "CEnemyRange.h"


CState* CStateIdle::HandleInput(CObject* _pObj) {
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if (KEYHOLD(KEY::LEFT))
        {
            pPlayer->SetObjDir(false);
            return new CStateMove();
        }
        if (KEYHOLD(KEY::RIGHT))
        {
            pPlayer->SetObjDir(true);
            return new CStateMove();
        }
        if (KEYTAP(KEY::A) && pPlayer->m_bCanSkill)
        {
            return new CStateSkill();
        }
        if (KEYTAP(KEY::S) && !pPlayer->m_bCanSkill)
        {
            return new CStateAppear();
        }
        if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
        {
            pPlayer->m_bCanDash = false;
            return new CStateDash();
        }
        if (KEYTAP(KEY::C))
        {
            if (KEYHOLD(KEY::DOWN))
            {
                pPlayer->m_vPos.y += 3;
                pPlayer->m_bIsGround = false;
                return new CStateFall();
            }
            return new CStateJump();
        }
        if (KEYTAP(KEY::X))
        {
            return new CStateAttack();
        }
        if (!pPlayer->IsGround())
            return new CStateFall();
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
            if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
                return new CStateDie();

            if (abs(PLAYERPOS.x - pEnemy->GetPos().x) < 400 && pEnemy->m_bIsGround)
                return new CStateTrace();

            if (!pEnemy->m_bIsGround)
                return new CStateFall();
        }
            break;
        case ENEMY_TYPE::WIZARD:
        {
            CEnemyRange* pEnemy = (CEnemyRange*)_pObj;
            if (pEnemy->m_tEnemyInfo.m_iHp <= 0)
                return new CStateDie();
            if (abs(PLAYERPOS.x - pEnemy->GetPos().x) < 400 && pEnemy->m_bIsGround)
                return new CStateTrace();

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
void CStateIdle::Update(CObject* _pPlayer) {
}

void CStateIdle::Enter(CObject* _pObj)
{
    switch (_pObj->GetObjType())
    {
    case OBJ_TYPE::PLAYER:
    {
        CPlayer* pPlayer = (CPlayer*)_pObj;
        if(pPlayer->m_bCanSkill)
            pPlayer->GetAnimator()->Play(L"Player_Idle", true);
        else
            pPlayer->GetAnimator()->Play(L"Player_Idle_Headless", true);
        pPlayer->m_strCurState = L"Idle";

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
    break;
    }
}

void CStateIdle::Exit(CObject* _pObj)
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


