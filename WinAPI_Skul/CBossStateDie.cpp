#include "pch.h"

#include "Stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"

CBossState* CBossStateDie::HandleInput(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
	{
		DELETEOBJECT(_pObj);
	}
	return nullptr;
}

void CBossStateDie::Update(CObject* _pObj)
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

	if (1.0f < m_fCurTime && m_fCurTime < 1.2f)
	{
	}
	else if (1.8f < m_fCurTime && m_fCurTime < 2.0f)
	{
		if (m_fCurTime < 1.9f && m_bOnceFunc)
		{
			AnimationChange(pBoss);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
		}
	}
	else if (3.0f < m_fCurTime && m_fCurTime < 6.0f)
	{
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(rand() % 300 - 150, rand() % 300 - 150) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(rand() % 300 - 150, rand() % 300 - 150) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(rand() % 300 - 150, rand() % 300 - 150) * DT);
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(0, 50) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, 85) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, 70) * DT);
	}
	else if (6.0f < m_fCurTime && m_fCurTime < 6.2f)
	{
		if (m_fCurTime < 6.1f && m_bOnceFunc)
		{
			LOG(L"카메라 흔들기 효과")
			SINGLE(CCameraManager)->CameraShaking(2000, 1.5f);
			SINGLE(CGameManager)->CreateEffect(L"Die_Smoke", L"texture\\effect\\ElderEnt_Die_Impact.png",
				pBoss->m_pHeadBottom->GetPos()+ Vec2(0, -120), 2.f, 2.f, rand()%2, 2.f);
			SINGLE(CGameManager)->CreateEffect(L"Die_Smoke", L"texture\\effect\\ElderEnt_Die_Impact.png",
				pBoss->m_pHeadBottom->GetPos() + Vec2(-300, -120), 2.f, 2.f, rand() % 2, 2.f);
			SINGLE(CGameManager)->CreateEffect(L"Die_Smoke", L"texture\\effect\\ElderEnt_Die_Impact.png",
				pBoss->m_pHeadBottom->GetPos() + Vec2(300, -120), 2.f, 2.f, rand() % 2, 2.f);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
		}
	}
}

void CBossStateDie::Enter(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fCurTime = 0.f;
	m_fNextAttackTime = 15.f;
	m_fNextAttackCurTime = 0.f;
	m_bOnceFunc = true;
	m_fOnceFuncTime = 0.5f;
	m_fOnceFuncCurTime = 0.f;
	pBoss->m_strCurState = L"Die";
	pBoss->m_pHeadTop->GetAnimator()->Play(L"BossHeadTop_Die", true);
	pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Bomb", true);
	pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Bomb", true);

	m_vOriginPos = pBoss->GetPos();
	pBoss->m_pBody->SetPos(pBoss->GetPos());
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, -70));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 100));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-380, 230));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+380, 230));

	SINGLE(CSoundManager)->Play(L"BossChangeIntro");
	SINGLE(CCameraManager)->WhiteOut(0.5f, 0);
}

void CBossStateDie::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos() + Vec2(0, 50));
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, 0));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 120));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-350, 180));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+350, 180));
}

void CBossStateDie::AnimationChange(CEnemyBoss* _pObj)
{
	SINGLE(CCameraManager)->WhiteOut(1.f , 1000);
	_pObj->m_pBody->GetAnimator()->Play(L"BossBody_End", true);
	_pObj->m_pHeadTop->GetAnimator()->Play(L"BossHeadTop_End", true);
	_pObj->m_pHeadBottom->GetAnimator()->Play(L"BossHeadBottom_End", true);
	_pObj->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_End", true);
	_pObj->m_pRightHand->GetAnimator()->Play(L"BossRightHand_End", true);
}
