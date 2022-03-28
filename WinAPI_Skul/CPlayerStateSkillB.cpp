#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CHunter.h"
#include "CLittleBorn.h"


CPlayerState* CPlayerStateSkillB::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (m_fCurTime >= m_fDuration)
		return new CPlayerStateIdle();

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
	return nullptr;
}

void CPlayerStateSkillB::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;



	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fCurTime += DT;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		CHunter* pPlayer = (CHunter*)_pObj;
		m_fCurTime += DT;
		if (KEYHOLD(KEY::S) && (0.1f < m_fCurTime && m_fCurTime < 0.2f))
		{
			pPlayer->GetAnimator()->Play(L"Hunter_AttackReady2", true);
		}
		if (KEYHOLD(KEY::S) && m_fCurTime > 0.2f &&
			!m_bIsAttack)
		{
			m_fDuration += DT;
			pPlayer->m_fCurChargeTime += DT;
			if (pPlayer->m_bCharged && m_bOnceFunc)
			{
				pPlayer->GetAnimator()->Play(L"Hunter_Charge_completed", true);
				SINGLE(CSoundManager)->Play(L"Hunter_Charge_Completed");
				m_fOnceFuncCurTime = 0;
				m_bOnceFunc = false;
			}
			else if (m_bOnceFunc)
			{
				pPlayer->GetAnimator()->Play(L"Hunter_Charging", true);
			}

		}
		if (KEYAWAY(KEY::S) && !m_bIsAttack)
		{
			if (pPlayer->m_bCharged)
				m_fDuration = m_fCurTime + 1.f;
			else
				m_fDuration = m_fCurTime + 0.5f;
			pPlayer->SkillB();
			m_bIsAttack = true;
		}
		break;
	}
	}
}

void CPlayerStateSkillB::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"SkillB";

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fCurTime = 0.f;
		m_fDuration = 0.5f;
		SINGLE(CGameManager)->CreateVfx(L"DisAppear", L"texture\\effect\\Enemy_Dead.png",
			pPlayer->GetPos(), 0.5f, 0.5f, pPlayer->GetObjDir());

		pPlayer->SkillB();

		SINGLE(CGameManager)->CreateVfx(L"Appear", L"texture\\effect\\Enemy_Appearance.png",
			pPlayer->GetPos(), 0.5f, 0.5f, pPlayer->GetObjDir());

		pPlayer->GetAnimator()->Play(L"LittleBorn_SkillRebone", true);
		SINGLE(CSoundManager)->Play(L"SkillB");
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		m_fDuration = 0.5f;
		m_fCurTime = 0.f;
		m_bOnceFunc = true;
		m_fOnceFuncTime = 1.0f;
		m_fOnceFuncCurTime = 0.f;
		pPlayer->GetAnimator()->Play(L"Hunter_AttackReady", true);
		SINGLE(CSoundManager)->Play(L"Hunter_DrawArrow");
		break;
	}
	}
}

void CPlayerStateSkillB::Exit(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;



	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		pPlayer->m_bCanSkill = true;
		pPlayer->m_fSkillCurTime = 0.f;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}
