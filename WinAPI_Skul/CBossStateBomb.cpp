#include "pch.h"
#include "stateheader.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"
#include "CProjectile.h"

CBossState* CBossStateBomb::HandleInput(CObject* _pObj)
{
	if (m_fNextAttackCurTime >= m_fNextAttackTime)
		return new CBossStateIdleP2();
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
		if (1.0f < m_fCurTime && m_fCurTime < 1.1f && m_bOnceFunc)
		{
			SINGLE(CGameManager)->CreateEffect(L"Bomb_Charging2", L"texture\\effect\\ElderEntP2_EnergyCorps_Charging_2.png",
				pBoss->m_pHeadTop->GetPos(), 1.f, 1.f, true, 1.f);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
		}
		Vec2 randVec = Vec2(rand() % 500 - 250, rand() % 500 - 250);
		//pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + randVec * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + randVec * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + randVec * DT);
	}
	else if (2.f < m_fCurTime && m_fCurTime < 2.3f)
	{
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + Vec2(0, -30) * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + Vec2(0, -400) * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + Vec2(0, -400) * DT);
	}
	else if (2.4f < m_fCurTime && m_fCurTime < 6.f)
	{
		if (m_fCurTime < 2.5f && m_bOnceFunc)
		{
			SINGLE(CGameManager)->CreateEffect(L"Bomb_Casting", L"texture\\effect\\ElderEntP2_EnergyCorps_Spark.png",
				pBoss->m_pHeadTop->GetPos(), 3.5f, 1.f, true, 1.f);
			SINGLE(CCameraManager)->CameraShaking(500.f, 5.f);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
		}
		Vec2 randVec = Vec2(rand() % 300 - 150, rand() % 300 - 150);
		pBoss->m_pBody->SetPos(pBoss->m_pBody->GetPos() + randVec * DT);
		pBoss->m_pHeadTop->SetPos(pBoss->m_pHeadTop->GetPos() + randVec * DT);
		pBoss->m_pHeadBottom->SetPos(pBoss->m_pHeadBottom->GetPos() + randVec * DT);
		if (m_bOnceFunc)
		{
			CreateBomb(_pObj);
			m_bOnceFunc = false;
			m_fOnceFuncCurTime = 0.f;
		}
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
	m_fOnceFuncTime = 0.2f;
	m_fOnceFuncCurTime = 0.f;
	pBoss->m_bIsPhaseChanged = true;
	pBoss->m_strCurState = L"Change";

	m_vOriginPos = pBoss->GetPos();
	pBoss->m_pBody->SetPos(pBoss->GetPos() + Vec2(0, 50));
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, 0));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 170));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-420, +240));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+420, +240));

	SINGLE(CGameManager)->CreateEffect(L"Bomb_Charging", L"texture\\effect\\ElderEntP2_EnergyCorps_Charging_1.png",
		pBoss->m_pHeadTop->GetPos(), 1.f, 1.f, true, 1.f);
	SINGLE(CSoundManager)->Play(L"BossBombFire");
}

void CBossStateBomb::Exit(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	pBoss->SetPos(m_vOriginPos);
	pBoss->m_pBody->SetPos(pBoss->GetPos() + Vec2(0, 50));
	pBoss->m_pHeadTop->SetPos(pBoss->GetPos() + Vec2(0, 0));
	pBoss->m_pHeadBottom->SetPos(pBoss->GetPos() + Vec2(30, 120));
	pBoss->m_pLeftHand->SetPos(pBoss->GetPos() + Vec2(-350, 180));
	pBoss->m_pRightHand->SetPos(pBoss->GetPos() + Vec2(+350, 180));
}

void CBossStateBomb::CreateBomb(CObject* _pObj)
{
	CEnemyBoss* pBoss = (CEnemyBoss*)_pObj;
	CObject* pObj = pBoss->m_pHeadTop;
	Vec2 startPos = pObj->GetPos() + Vec2(rand() % 1400 - 700, rand()%50 - 25) + Vec2(0, -100);
	//Vec2 vVelo = (PLAYERPOS - startPos).Normalize() * 300;
	Vec2 vVelo = Vec2(rand()%500 - 250, 500);
	SINGLE(CGameManager)->CreateEffect(L"Bomb_Emerge", L"texture\\effect\\ElderEntP2_EnergyCorps_Projectile_Emerge.png",
		startPos, 1.f, 1.f, true, 1.f);
	CProjectile* pProj = new CProjectile(OBJ_TYPE::PROJECTILE, _pObj,
		L"BossBomb", L"texture\\effect\\ElderEntP2_EnergyCorps_Projectile.png",
		5.f);
	pProj->SetPos(startPos);
	pProj->SetVelocity(vVelo);
	CREATEOBJECT(pProj);
	SINGLE(CSoundManager)->Play(L"BossBombReady");
	
}

