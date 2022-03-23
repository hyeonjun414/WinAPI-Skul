#include "pch.h"
#include "stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"

CBossState* CBossStateSweep::HandleInput(CObject* _pObj)
{
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
		return new CBossStateIdle();
	return nullptr;
}

void CBossStateSweep::Update(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fCurTime += DT * m_fStateSpeed;
	m_fNextAttackCurTime += DT * m_fStateSpeed;
	if (!m_bOnceFunc)
	{
		m_fOnceFuncCurTime += DT * m_fStateSpeed;
		if (m_fOnceFuncCurTime >= m_fOnceFuncTime)
		{
			m_bOnceFunc = true;
		}
	}
	if (m_fCurTime < 1.0f)
	{
		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + Vec2(-700, 30) * DT * m_fStateSpeed);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + Vec2(700, 30) * DT * m_fStateSpeed);
	}
	else if (1.f < m_fCurTime && m_fCurTime < 1.5f)
	{
		if (m_fCurTime < 1.1f && m_bOnceFunc)
		{
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
			SelectSweepHand(pBoss);
		}
	}
	else if (1.5f < m_fCurTime && m_fCurTime < 2.0f)
	{
		pBoss->SetPos(pBoss->GetPos() - m_vBodyVelocity * DT * m_fStateSpeed * 0.35f);
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() - m_vBodyVelocity * DT * m_fStateSpeed * 0.35f);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() - m_vHeadVelocity * DT * m_fStateSpeed * 0.4f);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() - m_vHeadVelocity * DT * m_fStateSpeed * 0.4f);
	}
	else if (2.0f < m_fCurTime && m_fCurTime < 2.5f)
	{

	}
	else if (2.5f < m_fCurTime && m_fCurTime < 3.5f)
	{
		if (m_fCurTime < 2.6f && m_bOnceFunc)
		{
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
			pBoss->Sweep(m_pSelectedHand);
		}
		pBoss->SetPos(pBoss->GetPos());
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(rand() % 500 - 250, rand() % 500 - 250) * DT * m_fStateSpeed);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(rand() % 500 - 250, rand() % 500 - 250) * DT * m_fStateSpeed);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(rand() % 500 - 250, rand() % 500 - 250) * DT * m_fStateSpeed);
		pBoss->SetPos(pBoss->GetPos() + m_vBodyVelocity * DT * m_fStateSpeed * 0.35f);
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + m_vBodyVelocity * DT * m_fStateSpeed * 0.35f);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + m_vHeadVelocity * DT * m_fStateSpeed * 0.4f);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + m_vHeadVelocity * DT * m_fStateSpeed * 0.4f);
		m_pSelectedHand->SetPos(m_pSelectedHand->GetPos() + m_vSweepVelocity * DT * m_fStateSpeed);
	}
	else if (4.0f < m_fCurTime && m_fCurTime < 4.5f)
	{
		pBoss->SetPos(pBoss->GetPos() - m_vBodyVelocity * DT * m_fStateSpeed * 0.35f);
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() - m_vBodyVelocity * DT * m_fStateSpeed * 0.35f);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() - m_vHeadVelocity * DT * m_fStateSpeed * 0.4f);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() - m_vHeadVelocity * DT * m_fStateSpeed * 0.4f);
	}


}

void CBossStateSweep::Enter(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fMoveTime = 1.f;
	m_fCurTime = 0.f;
	m_fNextAttackTime = 5.0f;
	m_fNextAttackCurTime = 0.f;
	m_bOnceFunc = true;
	m_fOnceFuncTime = 0.5f;
	m_fOnceFuncCurTime = 0.f;
	pBoss->m_strCurState = L"Sweep";
	if (pBoss->m_bIsPhaseChanged)
	{
		m_fStateSpeed = 1.2f;
		pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Sweep_P2", true);
		pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Sweep_P2", true);
	}
	else
	{
		m_fStateSpeed = 1.f;
		pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Sweep", true);
		pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Sweep", true);
	}
	m_vOriginPos = pBoss->GetPos();
}

void CBossStateSweep::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos());
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, -50));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 70));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-280, 100));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+280, 100));
}

void CBossStateSweep::SelectSweepHand(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	bool select = rand() % 2;
	m_pSelectedHand = select ? pBoss->m_pLeftHand : pBoss->m_pRightHand;
	m_vSweepVelocity = Vec2(select ? 2000 : -2000, 0);
	m_vBodyVelocity = m_vSweepVelocity/2 + Vec2(0, 200);
	m_vHeadVelocity = m_vSweepVelocity/2 + Vec2(0, 300);
}
