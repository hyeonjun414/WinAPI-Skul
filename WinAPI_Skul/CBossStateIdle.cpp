#include "pch.h"
#include "Stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"

CBossState* CBossStateIdle::HandleInput(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	if (0 >= pBoss->m_tEnemyInfo.m_iHp)
		return new CBossStateDie();
	if (0.5f >= pBoss->m_tEnemyInfo.m_iHp / (float)pBoss->m_tEnemyInfo.m_iMaxHp)
		return new CBossStateChange();
	
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
	{
		switch (m_eNextAction)
		{
		case BossPattern::SLAM:
			return new CBossStateSlam();
		case BossPattern::SWEEP:
			return new CBossStateSweep();
		}
	}
	return nullptr;
}

void CBossStateIdle::Update(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fCurTime += DT;
	m_fNextAttackCurTime += DT;
	if (m_fCurTime >= m_fMoveTime)
	{
		m_fMoveDir *= -1.f;
		m_fCurTime = 0.f;
	}
	// 위아래 기본 움직임
	pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + pBoss->m_tEnemyInfo.m_vVelocity * DT * m_fMoveDir * 0.15f);
	if (m_fCurTime >= 0.1f)
	{
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + pBoss->m_tEnemyInfo.m_vVelocity * DT * m_fMoveDir * 0.20f);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + pBoss->m_tEnemyInfo.m_vVelocity * DT * m_fMoveDir * 0.25f);
	}
	if (m_fCurTime >= 0.6f)
	{
		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + pBoss->m_tEnemyInfo.m_vVelocity * DT * m_fMoveDir * 0.15f);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + pBoss->m_tEnemyInfo.m_vVelocity * DT * m_fMoveDir * 0.15f);
	}
}

void CBossStateIdle::Enter(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fMoveDir = -1.f;
	m_fMoveTime = 1.f;
	m_fCurTime = 0.f;
	m_fNextAttackTime = 2.f;
	m_fNextAttackCurTime = 0.f;
	m_eNextAction = (BossPattern)(rand() % 2);
	pBoss->m_strCurState = L"Idle";
	if (pBoss->m_bIsPhaseChanged)
	{
		pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Idle_P2", true);
		pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Idle_P2", true);
	}
	else
	{
		pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Idle", true);
		pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Idle", true);
	}
	
	m_vOriginPos = pBoss->GetPos();
}

void CBossStateIdle::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos() + Vec2(0, 50));
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, 0));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 120));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-350, 180));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+350, 180));
}
