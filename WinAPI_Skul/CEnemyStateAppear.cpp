#include "pch.h"

#include "Stateheader.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CEffect.h"

#include "CEnemyMelee.h"

CEnemyState* CEnemyStateAppear::HandleInput(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    if (m_fCurTime >= m_fDuration)
        return new CEnemyStateIdle();

    return nullptr;
}

void CEnemyStateAppear::Update(CObject* _pObj)
{
    CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
    m_fCurTime += DT;
}

void CEnemyStateAppear::Enter(CObject* _pObj)
{
    CEnemy* pEnemy = (CEnemy*)_pObj;
    m_fCurTime = 0.f;
    m_fDuration = 1.0f;
    pEnemy->m_strCurState = L"Appear";
    pEnemy->GetAnimator()->Play(L"AppearEnemy", false);
}

void CEnemyStateAppear::Exit(CObject* _pObj)
{
    CEnemyMelee* pEnemy = (CEnemyMelee*)_pObj;
}
