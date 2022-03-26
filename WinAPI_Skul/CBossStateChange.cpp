#include "pch.h"
#include "stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"

CBossState* CBossStateChange::HandleInput(CObject* _pObj)
{
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
		return new CBossStateIdleP2();
	return nullptr;
}

void CBossStateChange::Update(CObject* _pObj)
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
	if (m_fCurTime < 1.0f)
	{
	}
	else if (1.0f < m_fCurTime && m_fCurTime < 1.5f)
	{
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(0, -100) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, -200) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, -250) * DT);
		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + Vec2(-300, -500) * DT);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + Vec2(+300, -500) * DT);
	}
	else if (1.5f < m_fCurTime && m_fCurTime < 1.8f)
	{
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(0, 500) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, 700) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, 700) * DT);
		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + Vec2(0, 1420) * DT);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + Vec2(0, 1420) * DT);
	}
	else if (1.8f < m_fCurTime && m_fCurTime < 2.0f)
	{
		if (m_fCurTime < 1.9f && m_bOnceFunc)
		{
			AnimationChange(pBoss);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
			pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, 30));
		}
	}
	else if (2.0f < m_fCurTime && m_fCurTime < 6.f)
	{
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(rand() % 300 - 150, rand() % 300 - 150) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(rand() % 300 - 150, rand() % 300 - 150) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(rand() % 300 - 150, rand() % 300 - 150) * DT);
	}
	else if (6.f < m_fCurTime && m_fCurTime < 6.2f)
	{
		if (m_fCurTime < 6.1f && m_bOnceFunc)
		{
			HandAnimChange(pBoss);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
		}
	}
	else
	{
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(0, -20) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, -20) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, -20) * DT);
		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + Vec2(100, -50) * DT);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + Vec2(-100, -50) * DT);
	}

}

void CBossStateChange::Enter(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	if (pBoss->m_bIsPhaseChanged)
	{
		pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Slam_P2", true);
		pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Slam_P2", true);
	}
	else
	{
		pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Slam", true);
		pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Slam", true);
	}
	m_fMoveTime = 1.f;
	m_fCurTime = 0.f;
	m_fNextAttackTime = 7.0f;
	m_fNextAttackCurTime = 0.f;
	m_bOnceFunc = true;
	m_fOnceFuncTime = 0.5f;
	m_fOnceFuncCurTime = 0.f;
	pBoss->m_bIsPhaseChanged = true;
	pBoss->m_strCurState = L"Change";
	SINGLE(CCameraManager)->WhiteOut(0.5f, 0);

	m_vOriginPos = pBoss->GetPos();
	pBoss->m_pBody->SetPos(pBoss->GetPos());
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, -70));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 50));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-350, 0));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+350, 0));

	SINGLE(CSoundManager)->Play(L"BossChangeIntro");
}

void CBossStateChange::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos() + Vec2(0, 50));
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, 0));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 120));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-350, 180));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+350, 180));
}

void CBossStateChange::AnimationChange(CEnemyBoss* _pObj)
{
	SINGLE(CCameraManager)->WhiteOut(4.f, 2000);

	SINGLE(CSoundManager)->Play(L"BossSlam");
	SINGLE(CSoundManager)->Play(L"BossSlam");
	SINGLE(CSoundManager)->Play(L"BossRoar");
	_pObj->m_pBody->GetAnimator()->Play(L"BossBody_P2", true);
	_pObj->m_pHeadTop->GetAnimator()->Play(L"BossHeadTop_P2", true);
	_pObj->m_pHeadBottom->GetAnimator()->Play(L"BossHeadBottom_P2", true);
	_pObj->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Slam_P2", true);
	_pObj->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Slam_P2", true);
}

void CBossStateChange::HandAnimChange(CEnemyBoss* _pObj)
{
	_pObj->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Idle_P2", true);
	_pObj->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Idle_P2", true);
}
