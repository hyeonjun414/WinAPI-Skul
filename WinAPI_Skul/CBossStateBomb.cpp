#include "pch.h"
#include "stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"

CBossState* CBossStateBomb::HandleInput(CObject* _pObj)
{
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
		return new CBossStateIdle();
	return nullptr;
}

void CBossStateBomb::Update(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fCurTime += DT;
	m_fNextAttackCurTime += DT;
	if (!m_bOnceFunc)
	{
		m_fOnceFuncCurTime += DT;
		if (m_fOnceFuncCurTime >= m_fOnceFuncTime)
		{
			m_bOnceFunc = true;
			m_fOnceFuncCurTime = 0.f;
		}
	}

	if (m_fCurTime < 2.0f)
	{
		Vec2 randVec = Vec2(rand() % 500 - 250, rand() % 500 - 250);
		//pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + randVec * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + randVec * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + randVec * DT);
	}
	else if (1.0f < m_fCurTime && m_fCurTime < 1.5f)
	{
	}
	else if (1.5f < m_fCurTime && m_fCurTime < 1.8f)
	{
	}
	else if (1.8f < m_fCurTime && m_fCurTime < 2.0f)
	{
	}
	else if (2.0f < m_fCurTime && m_fCurTime < 6.f)
	{
	}
	else if (6.f < m_fCurTime && m_fCurTime < 6.2f)
	{
	}
	else
	{}

}

void CBossStateBomb::Enter(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Bomb", true);
	pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Bomb", true);
	m_fMoveTime = 1.f;
	m_fCurTime = 0.f;
	m_fNextAttackTime = 7.0f;
	m_fNextAttackCurTime = 0.f;
	m_bOnceFunc = true;
	m_fOnceFuncTime = 0.5f;
	m_fOnceFuncCurTime = 0.f;
	pBoss->m_bIsPhaseChanged = true;
	pBoss->m_strCurState = L"Change";

	m_vOriginPos = pBoss->GetPos();
	pBoss->m_pBody->SetPos(pBoss->GetPos() + Vec2(0, 50));
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, 0));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 170));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-360, +200));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+360, +200));

	ChargingEffect(pBoss->m_pHeadTop);
}

void CBossStateBomb::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos());
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, -50));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 70));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-280, 100));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+280, 100));
}

void CBossStateBomb::ChargingEffect(CObject* _pObj)
{
	SINGLE(CGameManager)->CreateEffect(L"Bomb_Charging", L"texture\\effect\\ElderEntP2_EnergyCorps_Charging.png",
		_pObj->GetPos(), 2.f, 2.f, true);
}

