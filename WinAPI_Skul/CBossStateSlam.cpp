#include "pch.h"
#include "stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"

CBossState* CBossStateSlam::HandleInput(CObject* _pObj)
{
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
		return new CBossStateIdle();
	return nullptr;
}

void CBossStateSlam::Update(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fCurTime += DT;
	m_fNextAttackCurTime += DT;
	if (!m_bOnceFunc)
	{
		if (m_fOnceFuncCurTime < m_fOnceFuncTime)
		{
			m_bOnceFunc = true;
			m_fOnceFuncCurTime = 0.f;
		}
	}
	if (m_fCurTime < 0.5f)
	{
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, -200) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, -250) * DT);

		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + Vec2(-150, -500) * DT);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + Vec2(+150, -500) * DT);
	}
	else if (0.5f < m_fCurTime && m_fCurTime < 1.0f)
	{
		SelectSlamHand(_pObj);
		SetSlamVelocity(m_pSelectedHand);
		
	}
	else if(1.0f < m_fCurTime && m_fCurTime < 1.5f)
	{
		if (m_fCurTime < 2.6f && m_bOnceFunc)
			pBoss->Slam(m_pSelectedHand);

		m_pSelectedHand->SetPos(m_pSelectedHand->GetPos() + m_vSlamVelocity * DT);
		if (m_fCurTime > 1.46f && m_bOnceFunc)
			SINGLE(CCameraManager)->CameraShaking(1000, 1.f);
	}
	else if (1.5f < m_fCurTime && m_fCurTime < 2.0f)
	{
		m_pSelectedHand->SetPos(m_pSelectedHand->GetPos() - m_vSlamVelocity * DT);
		
	}
	else if (2.0f < m_fCurTime && m_fCurTime < 2.5f)
	{
		SelectSlamHand(_pObj);
		SetSlamVelocity(m_pSelectedHand);
	}
	else if (2.5f < m_fCurTime && m_fCurTime < 3.0f)
	{
		if (m_fCurTime < 2.6f && m_bOnceFunc)
			pBoss->Slam(m_pSelectedHand);
		m_pSelectedHand->SetPos(m_pSelectedHand->GetPos() + m_vSlamVelocity * DT);
		if (m_fCurTime > 2.96f && m_bOnceFunc)
		{
			SINGLE(CCameraManager)->CameraShaking(1000, 1.f);
			LOG(L"카메라 흔들기");
		}
	}
	else if (3.0f < m_fCurTime && m_fCurTime < 3.5f)
	{
		m_pSelectedHand->SetPos(m_pSelectedHand->GetPos() - m_vSlamVelocity * DT);
	}
	else if (3.5f < m_fCurTime && m_fCurTime < 4.0f)
	{
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, 200) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, 250) * DT);

		pBoss->m_pLeftHand->SetPos(pBoss->m_pLeftHand->GetPos() + Vec2(150, 500) * DT);
		pBoss->m_pRightHand->SetPos(pBoss->m_pRightHand->GetPos() + Vec2(-150, 500) * DT);
	}


}

void CBossStateSlam::Enter(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	m_fMoveDir = -1.f;
	m_fMoveTime = 1.f;
	m_fCurTime = 0.f;
	m_fNextAttackTime = 4.f;
	m_fNextAttackCurTime = 0.f;
	m_fSlamTime = 0.5f;
	pBoss->m_strCurState = L"Slam";
	pBoss->m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Slam", true);
	pBoss->m_pRightHand->GetAnimator()->Play(L"BossRightHand_Slam", true);
	m_vOriginPos = pBoss->GetPos();
}

void CBossStateSlam::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos());
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, -50));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 70));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-280, 100));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+280, 100));
}

void CBossStateSlam::SetSlamVelocity(CObject* _pObj)
{
	Vec2 dir = (PLAYERPOS - _pObj->GetPos()).Normalize();
	//float velocity = (PLAYERPOS - _pObj->GetPos()).Length() / 0.5f;
	
	m_vSlamVelocity = dir * 800;
}

void CBossStateSlam::SelectSlamHand(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	// 왼손이 플레이어와 더 가까울때
	if ((PLAYERPOS - pBoss->m_pLeftHand->GetPos()).Length() <
		(PLAYERPOS - pBoss->m_pRightHand->GetPos()).Length())
	{
		m_pSelectedHand = pBoss->m_pLeftHand;

	}
	// 오른쪽이 플레이어와 더가까울때
	else
	{
		m_pSelectedHand = pBoss->m_pRightHand;
	}
}
